#include <Python.h>
#include <stdlib.h>
#include <time.h>


typedef enum { TRUE = 1, FALSE = 0 } Bool;


#define ODD(num) ((num) & 1)
#define EVEN(num) (!ODD(num))


unsigned long long ModularPower(unsigned long long base, unsigned long long exponent,
    const unsigned long long modulu)
{
    unsigned long long result = 1;

    base %= modulu;

    while (0 < exponent)
    {
        if (ODD(exponent))
        {
            result = (result * base) % modulu;
        }

        exponent >>= 1; // exponent /= 2;
        base = (base * base) % modulu;
    }

    return result;
}

Bool TestOneCase(unsigned long long powerExponent, const unsigned long long number)
{
    const unsigned long long powerBase = (rand() % (number - 4)) + 2;

    unsigned long long powerResult = ModularPower(powerBase, powerExponent, number);

    if (1 == powerResult || (number - 1) == powerResult)
    {
        return TRUE;
    }

    while ((number - 1) != powerExponent && 1 != powerResult && (number - 1) != powerResult)
    {
        powerResult = (powerResult * powerResult) % number;
        powerExponent <<= 1; // powerExponent *= 2;
    }

    return (number - 1) == powerResult;
}

unsigned long long GetPowerExponent(const unsigned long long number)
{
    unsigned long long result = number - 1;
    while (EVEN(result))
    {
        result >>= 1; // result /= 2;
    }
    return result;
}

PyDoc_STRVAR(is_prime_doc, "is_prime(number, repeat_percents=0.5, /)\n"
"--\n"
"Returns True when number is a prime, and false otherwise.\n"
"Makes 'repeat_percents' iterations, as a fraction. Should be between 0 and 1.");

PyObject * is_prime(PyObject *self, PyObject *args)
{
    unsigned long long number = 0;
    double repeatPercents = 0.25;

    if (!PyArg_ParseTuple(args, "K|d", &number, &repeatPercents))
    {
        return NULL;
    }

    if (repeatPercents < 0 || 1 < repeatPercents)
    {
        PyErr_SetString(PyExc_ValueError, "The parameter 'repeat_percents' should be between 0 and 1");
        return NULL;
    }

    if (number <= 1)
    {
        PyErr_SetString(PyExc_ValueError, "Cannot determine primality for <=1");
        return NULL;
    }

    if (4 == number)
    {
        return PyBool_FromLong(FALSE);
    }

    if (number <= 5)
    {
        return PyBool_FromLong(TRUE);
    }

    const unsigned long long powerExponent = GetPowerExponent(number);

    const int repeatTimes = (int)(repeatPercents * number);
    for (int i = 0; i < repeatTimes; i++)
    {
        if (!TestOneCase(powerExponent, number))
        {
            return PyBool_FromLong(FALSE);
        }
    }
    return PyBool_FromLong(TRUE);
}


static PyMethodDef miller_rabin_primarility_functions[] = {
    { "is_prime", (PyCFunction)is_prime, METH_VARARGS, is_prime_doc },

    { NULL, NULL, 0, NULL } /* marks end of array */
};


int exec_miller_rabin_primarility(PyObject *module)
{
    PyModule_AddFunctions(module, miller_rabin_primarility_functions);

    PyModule_AddStringConstant(module, "__author__", "Chayim Refael Friedman");
    PyModule_AddStringConstant(module, "__version__", "1.0.0");
    PyModule_AddIntConstant(module, "year", 2019);

    return 0; /* success */
}

PyDoc_STRVAR(miller_rabin_primarility_doc, "A function checks for primality using the Miller-Rabin Algorithm.");

static PyModuleDef_Slot miller_rabin_primarility_slots[] = {
    { Py_mod_exec, exec_miller_rabin_primarility },
    { 0, NULL }
};

static PyModuleDef miller_rabin_primarility_def = {
    PyModuleDef_HEAD_INIT,
    "miller_rabin_primality",
    miller_rabin_primarility_doc,
    0,              /* m_size */
    NULL,           /* m_methods */
    miller_rabin_primarility_slots,
    NULL,           /* m_traverse */
    NULL,           /* m_clear */
    NULL,           /* m_free */
};

PyMODINIT_FUNC PyInit_miller_rabin_primarility()
{
    Py_Initialize();

    srand((unsigned)time(NULL));

    return PyModuleDef_Init(&miller_rabin_primarility_def);
}
