#define PY_SSIZE_T_CLEAN
#include <Python.h>


typedef struct {
    PyDictObject list;
    const char *buffer;
    size_t len;
} CachedDictObject;

static PyObject *
CachedDict_get_cache(CachedDictObject *self, PyObject *unused)
{
    // TODO placeholder
    return PyBytes_FromStringAndSize(self->buffer, self->len);
}

static PyMethodDef CachedDict_methods[] = {
    {"get_cache", (PyCFunction) CachedDict_get_cache, METH_NOARGS,
     PyDoc_STR("get cached string")},
    {NULL},
};


static int
CachedDict_init(CachedDictObject *self, PyObject *args, PyObject *kwds)
{
    if (PyDict_Type.tp_init((PyObject *) self, args, kwds) < 0)
        return -1;
//     todo check kwds
    self->buffer = 0;
    self->len = 0;
    return 0;
}

static PyTypeObject CachedDictType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "ujson.CachedDict",
    .tp_doc = "CachedDict objects",
    .tp_basicsize = sizeof(CachedDictObject),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_init = (initproc) CachedDict_init,
    .tp_methods = CachedDict_methods,
};

static CachedDictObject*
new_cacheddict()
{
    CachedDictObject* obj = (CachedDictObject*)PyObject_New(CachedDictObject, &CachedDictType);

    PyObject *args = PyTuple_New(0);
    PyObject *kwargs = Py_BuildValue("{s:i}", "b", 5);
    CachedDictType.tp_init((PyObject*)obj, args, kwargs);
    Py_DECREF(kwargs);
    Py_DECREF(args);

    return obj;
}


static PyModuleDef cacheddictmodule = {
    PyModuleDef_HEAD_INIT,
    .m_name = "cacheddict",
    .m_doc = "Example module that creates an extension type.",
    .m_size = -1,
};

PyMODINIT_FUNC
PyInit_cacheddict(void)
{
    PyObject *m;
    CachedDictType.tp_base = &PyDict_Type;
    if (PyType_Ready(&CachedDictType) < 0)
        return NULL;

    m = PyModule_Create(&cacheddictmodule);
    if (m == NULL)
        return NULL;

    Py_INCREF(&CachedDictType);
    if (PyModule_AddObject(m, "CachedDict", (PyObject *) &CachedDictType) < 0) {
        Py_DECREF(&CachedDictType);
        Py_DECREF(m);
        return NULL;
    }

    return m;
}
