#define PY_SSIZE_T_CLEAN
#include <Python.h>
#undef B0

#include "python_code_handler.hpp"

static int numargs=0;

/* Return the number of arguments of the application command line */
static PyObject*
emb_numargs(PyObject *self, PyObject *args)
{
    if(!PyArg_ParseTuple(args, ":numargs"))
        return NULL;
    return PyLong_FromLong(numargs);
}

static PyMethodDef EmbMethods[] = {
    {"numargs", emb_numargs, METH_VARARGS,
     "Return the number of arguments received by the process."},
    {NULL, NULL, 0, NULL}
};

static PyModuleDef EmbModule = {
    PyModuleDef_HEAD_INIT, "emb", NULL, -1, EmbMethods,
    NULL, NULL, NULL, NULL
};

static PyObject*
PyInit_emb(void)
{
    return PyModule_Create(&EmbModule);
}

void python_run_code(QString* code)
{
    // Инициализировать интерпретатор Python
    int argc = 1;
    char* argv[] = { (char*)"RengaPythonShell" };
    wchar_t *program = Py_DecodeLocale(argv[0], NULL);
    numargs = argc;
    PyImport_AppendInittab("emb", &PyInit_emb);

    if (program == NULL) {
        fprintf(stderr, "Fatal error: cannot decode argv[0]\n");
        exit(1);
    }
    Py_SetProgramName(program);  /* optional but recommended */
    Py_Initialize();

    PyRun_SimpleString(code->toStdString().c_str());
    if (Py_FinalizeEx() < 0) {
        PyErr_Print();
        exit(120);
    }

    PyMem_RawFree(program);
    python_clear();
}

void python_clear() {
    // Вернуть ресурсы системе
    //Py_XDECREF(pDict);
    //Py_XDECREF(pModule);
    //Py_XDECREF(pName);


    // Выгрузка интерпритатора Python
    Py_Finalize();
}
