
#include <Python.h>
#include <modsupport.h>
#include <iostream>

class extension {
public:
  extension() {
    static PyMethodDef methods[] = {
      {"hello", &hello, METH_VARARGS, "say hello"},
      {"add", &add, METH_VARARGS, "add two ints"},
      {"callback", &callback, METH_VARARGS, "call the argument"},
      {0, 0, 0, 0}
    };
    module = Py_InitModule("extension", methods);
  }

private:
  PyObject *module = nullptr;

  static PyObject *hello(PyObject *self, PyObject *args) {
    char *str;
    PyArg_ParseTuple(args, "s", &str);
    std::cout << "hello " << str << "\n";
    Py_RETURN_NONE;
  }

  static PyObject *add(PyObject *self, PyObject *args) {
    int a, b;
    PyArg_ParseTuple(args, "ii", &a, &b);
    return PyInt_FromLong(a + b);
  }

  static PyObject *callback(PyObject *self, PyObject *args) {
    PyObject *func;
    PyArg_ParseTuple(args, "O", &func);
    if (PyCallable_Check(func)) {
      PyObject *arglist = Py_BuildValue("(i)", 1234);
      PyObject_CallObject(func, arglist);
      Py_DECREF(arglist);
    }
    Py_RETURN_NONE;
  }
};


PyMODINIT_FUNC
initextension() {
  extension *e = new extension();
}

