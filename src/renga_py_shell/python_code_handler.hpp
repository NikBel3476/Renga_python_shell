#define PY_SSIZE_T_CLEAN
#pragma push_macro("slots")
#undef slots
#include <Python.h>
#pragma pop_macro("slots")
#undef B0

#ifndef PYTHON_CODE_HANDLER_HPP
#define PYTHON_CODE_HANDLER_HPP


#include <QString>
#include <QTextEdit>

class QTextEdit;

#include "python_code_handler.hpp"
QTextEdit* console;
/* Return the number of arguments of the application command line */
PyObject* renga_tools_print(PyObject *self, PyObject *args)
{
    const char *command;
    int sts;

    if (!PyArg_ParseTuple(args, "s", &command))
        return NULL;

    console->append(command);
    return PyUnicode_FromString(command);
    //return PyLong_FromLong(numargs);
}
//Пречисляет методы доступные в пакете
PyMethodDef renga_tools_Methods[] = {
    {"print", renga_tools_print, METH_VARARGS,
     "Return the number of arguments received by the process."},
    {NULL, NULL, 0, NULL}
};

//Прогружает модуль с функциями в Python
PyModuleDef renga_tools_Module = {
    PyModuleDef_HEAD_INIT, "renga_tools", NULL, -1, renga_tools_Methods,
    NULL, NULL, NULL, NULL
};

//Создает модуль в Python
PyObject* PyInit_renga_tools(void)
{
    return PyModule_Create(&renga_tools_Module);
}

void python_clear() {
    // Вернуть ресурсы системе
    //Py_XDECREF(pDict);
    //Py_XDECREF(pModule);
    //Py_XDECREF(pName);


    // Выгрузка интерпритатора Python
    Py_Finalize();
}

void python_run_code(QString* code, QTextEdit* console_input)
{
    console = console_input;
    // Инициализировать интерпретатор Python
    int argc = 1;
    char* argv[] = { (char*)"RengaPythonShell" };
    wchar_t *program = Py_DecodeLocale(argv[0], NULL);
    //numargs = argc;
    PyImport_AppendInittab("renga_tools", &PyInit_renga_tools);

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

#endif // PYTHON_CODE_HANDLER_HPP
