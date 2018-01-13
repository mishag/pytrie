#include <Python.h>

#include <trie.h>

typedef struct {
    PyObject_HEAD
    TrieMap<PyObject*>   map;
} Trie;

static void Trie_dealloc(Trie * self)
{
    Py_TYPE(self)->tp_free((PyObject*)self);
}

static PyObject* Trie_new(PyTypeObject *type,
                          PyObject     *args,
                          PyObject     *kwds)
{
    Trie * self;

    self = (Trie*)type->tp_alloc(type, 0);

    return (PyObject *)self;
}

static int Trie_init(Trie      *self,
                     PyObject  *args,
                     PyObject  *kwds)
{
    return 0;
}

static PyObject * Trie_size(Trie *self)
{
    const size_t len = self->map.size();

    return PyLong_FromSize_t(len);
}


static PyTypeObject trieType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "trie.Trie",             /* tp_name */
    sizeof(Trie),            /* tp_basicsize */
    0,                         /* tp_itemsize */
    0,                         /* tp_dealloc */
    0,                         /* tp_print */
    0,                         /* tp_getattr */
    0,                         /* tp_setattr */
    0,                         /* tp_reserved */
    0,                         /* tp_repr */
    0,                         /* tp_as_number */
    0,                         /* tp_as_sequence */
    0,                         /* tp_as_mapping */   /**** Implement ****/
    0,                         /* tp_hash  */
    0,                         /* tp_call */
    0,                         /* tp_str */
    0,                         /* tp_getattro */
    0,                         /* tp_setattro */
    0,                         /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT,        /* tp_flags */
    "Trie objects",           /* tp_doc */
};


static PyModuleDef triemodule = {
    PyModuleDef_HEAD_INIT,
    "trie",
    "Trie module",
    -1,
    NULL, NULL, NULL, NULL, NULL
};


PyMODINIT_FUNC
PyInit_trie(void)
{
    PyObject* m;

    trieType.tp_new = PyType_GenericNew;
    trieType.tp_itemsize = &Trie_size;

    if (PyType_Ready(&trieType) < 0)
        return NULL;

    m = PyModule_Create(&triemodule);
    if (m == NULL)
        return NULL;

    Py_INCREF(&trieType);
    PyModule_AddObject(m, "Trie", (PyObject *)&trieType);
    return m;
}
