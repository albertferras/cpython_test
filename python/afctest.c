#include <Python.h>
#include "cacheddict.h"

PyObject* foo(PyObject* self, PyObject *args, PyObject *kwargs);

static PyMethodDef afcMethods[] = {
  {"foo", (PyCFunction) foo, METH_VARARGS | METH_KEYWORDS, "Test stuff."},
  {NULL, NULL, 0, NULL}       /* Sentinel */
};

static struct PyModuleDef moduledef = {
  PyModuleDef_HEAD_INIT,
  "afctest",
  0,              /* m_doc */
  -1,             /* m_size */
  afcMethods,   /* m_methods */
  NULL,           /* m_reload */
  NULL,           /* m_traverse */
  NULL,           /* m_clear */
  NULL            /* m_free */
};

PyObject *PyInit_afctest(void)
{
  PyObject *module;
  PyObject *version_string;

  module = PyModule_Create(&moduledef);
  PyInit_cacheddict();

  if (module == NULL)
  {
    return NULL;
  }

  version_string = PyUnicode_FromString ("0.1");
  PyModule_AddObject (module, "__version__", version_string);

  return module;
}
