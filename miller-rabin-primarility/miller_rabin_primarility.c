#include <Python.h>
#include <stdlib.h>
#include <time.h>


typedef enum { TRUE = 1, FALSE = 0 } Bool;


#define ODD(num) ((num) & 1)
#define EVEN(num) (!ODD(num))


unsigned long long GCD(unsigned long long a, unsigned long long b)
{
    while (0 != b)
    {
        unsigned long long temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

Bool AreCoprimeNumbers(unsigned long long a, unsigned long long b)
{
    return GCD(a, b) == 1;
}

unsigned long long ModularPower(unsigned long long base, unsigned long long exponent,
    unsigned long long modulu)
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

PyDoc_STRVAR(is_prime_doc, "is_prime(number, /)\n"
"--\n"
"Returns True when number is a prime, and false otherwise.");

PyObject * is_prime(PyObject *self, PyObject *oNumber)
{
    unsigned long long number = PyLong_AsUnsignedLongLong(oNumber);

    if (PyErr_Occurred())
    {
        return NULL;
    }

    unsigned long long powerBase = (rand() % (number - 2)) + 2;

    if (!AreCoprimeNumbers(number, powerBase))
    {
        return PyBool_FromLong(FALSE);
    }

    Py_RETURN_NONE;
}


static PyMethodDef miller_rabin_primarility_functions[] = {
    { "is_prime", (PyCFunction)is_prime, METH_O, is_prime_doc },

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
