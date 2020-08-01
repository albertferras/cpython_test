#include <Python.h>
#include "cacheddict.h"

PyObject* foo(PyObject* self, PyObject *args, PyObject *kwargs) {
    return new_cacheddict();
}
