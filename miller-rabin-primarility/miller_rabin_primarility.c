#include <Python.h>


typedef enum { TRUE = 1, FALSE = 0 } Bool;


long long GCD(long long a, long long b)
{
    while (0 != b)
    {
        int temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

Bool AreCoprimeNumbers(long long a, long long b)
{
    return GCD(a, b) == 1;
}

PyDoc_STRVAR(is_prime_doc, "is_prime(number, /)\n"
"--\n"
"Returns True when number is a prime, and false otherwise.");

PyObject * is_prime(PyObject *self, PyObject *oNumber)
{
    long long number = PyLong_AsLongLong(oNumber);

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
    return PyModuleDef_Init(&miller_rabin_primarility_def);
}
