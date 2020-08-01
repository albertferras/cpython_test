#ifndef CACHEDDICT_H
#define CACHEDDICT_H

#include <Python.h>

typedef struct {
    PyDictObject list;
    const char *buffer;
    size_t len;
} CachedDictObject;

CachedDictObject* new_cacheddict();

PyMODINIT_FUNC PyInit_cacheddict(void);

#endif
