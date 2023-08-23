#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include "sym.h"
#include "ddg.h"
#include "ncm.h"
#include "symnmf.h"
#include "utils.h"



MAT* convertPyMatToCMat(PyObject* matrix, int cols, int rows){
    int i;
    int j;
    double** vals;
    PyObject* rowPy;
    PyObject* item;
    MAT* mat = initMat(cols, rows);

    for (i = 0; i < cols; i++) {
        rowPy = PyList_GetItem(matrix, i);
        for (j = 0; j < rows; j++) {
            item = PyList_GetItem(rowPy, j);
            mat->vals[i][j] = PyFloat_AsDouble(item);
        }
    }
    return mat;
}

static PyObject* sym(PyObject *self, PyObject *args){
    
    pyObject* xVector;
    int xNumOfVectors, xVectorLength;

    MAT* cVectors;
    MAT* symMat;

    PyObject* pyMatrix;
    PyObject* pyRow;
    PyObject* pyValue;

    int symNumOfVectors, symVectorLength;
    double** symVals;
    

    if(!PyArg_ParseTuple(args, "Oii", &xVector, &xNumOfVectors, &xVectorLength)) {
        return NULL;
    }
    
    cVectors = convertPyMatToCMat(xVector, xNumOfVectors, xVectorLength);

    symMat = createSymMat(cVectors);
    freeMat(cVectors);

    symNumOfVectors = symMat->cols;
    symVectorLength = symMat->rows;
    symVals = symMat->vals;
    
    pyMatrix = PyList_New(symNumOfVectors);  // Create a new Python list object for the rows

    if (pyMatrix) {
        for (int i = 0; i < symNumOfVectors; i++) {
            pyRow = PyList_New(symVectorLength);  // Create a new Python list object for each row
            if (pyRow) {
                for (int j = 0; j < symVectorLength; j++) {
                    pyValue = Py_BuildValue("d", symVals[i][j]);  // Convert C value to Python float
                    PyList_SET_ITEM(pyRow, j, pyValue);  // Set the value in the Python row list
                }
            }

            PyList_SET_ITEM(pyMatrix, i, pyRow);  // Set the row list in the Python matrix list
        }
    }

    return pyMatrix;
}

static PyObject* ddg(PyObject *self, PyObject *args){
    
    pyObject* xVector;
    int xNumOfVectors, xVectorLength;

    MAT* cVectors;
    MAT* ddgMat;

    PyObject* pyMatrix;
    PyObject* pyRow;
    PyObject* pyValue;

    int ddgNumOfVectors, ddgVectorLength;
    double** ddgVals;
    

    if(!PyArg_ParseTuple(args, "Oii", &xVector, &xNumOfVectors, &xVectorLength)) {
        return NULL;
    }
    
    cVectors = convertPyMatToCMat(xVector, xNumOfVectors, xVectorLength);

    ddgMat = createDdgMat(cVectors);
    freeMat(cVectors);

    ddgNumOfVectors = symMat->cols;
    ddgVectorLength = symMat->rows;
    ddgVals = symMat->vals;
    
    pyMatrix = PyList_New(ddgNumOfVectors);  // Create a new Python list object for the rows

    if (pyMatrix) {
        for (int i = 0; i < ddgNumOfVectors; i++) {
            pyRow = PyList_New(ddgVectorLength);  // Create a new Python list object for each row
            if (pyRow) {
                for (int j = 0; j < ddgVectorLength; j++) {
                    pyValue = Py_BuildValue("d", ddgVals[i][j]);  // Convert C value to Python float
                    PyList_SET_ITEM(pyRow, j, pyValue);  // Set the value in the Python row list
                }
            }

            PyList_SET_ITEM(pyMatrix, i, pyRow);  // Set the row list in the Python matrix list
        }
    }

    return pyMatrix;
}

static PyObject* norm(PyObject *self, PyObject *args){
    
    pyObject* xVector;
    int xNumOfVectors, xVectorLength;

    MAT* cVectors;
    MAT* normMat;

    PyObject* pyMatrix;
    PyObject* pyRow;
    PyObject* pyValue;

    int normNumOfVectors, normVectorLength;
    double** normVals;
    

    if(!PyArg_ParseTuple(args, "Oii", &xVector, &xNumOfVectors, &xVectorLength)) {
        return NULL;
    }
    
    cVectors = convertPyMatToCMat(xVector, xNumOfVectors, xVectorLength);

    normMat = createNsmMat(cVectors);
    freeMat(cVectors);

    normNumOfVectors = symMat->cols;
    normVectorLength = symMat->rows;
    normVals = symMat->vals;
    
    pyMatrix = PyList_New(normNumOfVectors);  // Create a new Python list object for the rows

    if (pyMatrix) {
        for (int i = 0; i < normNumOfVectors; i++) {
            pyRow = PyList_New(normVectorLength);  // Create a new Python list object for each row
            if (pyRow) {
                for (int j = 0; j < normVectorLength; j++) {
                    pyValue = Py_BuildValue("d", normVals[i][j]);  // Convert C value to Python float
                    PyList_SET_ITEM(pyRow, j, pyValue);  // Set the value in the Python row list
                }
            }

            PyList_SET_ITEM(pyMatrix, i, pyRow);  // Set the row list in the Python matrix list
        }
    }

    return pyMatrix;
}

static PyObject* symnmf(PyObject *self, PyObject *args){
    
    pyObject* hMat;
    pyObject* normMat;
    int hNumOfVectors, hVectorLength;
    int normNumOfVectors, normVectorLength;
    int iter;
    double eps;

    MAT* cHInitMat, cNormMat;
    MAT* finalHMat;

    PyObject* pyMatrix;
    PyObject* pyRow;
    PyObject* pyValue;

    int finalHNumOfVectors, finalHVectorLength;
    double** finalHVals;
    

    if(!PyArg_ParseTuple(args, "OOiiiiid", &hMat, &hNumOfVectors, &hVectorLength, &normMat, &normNumOfVectors, &normVectorLength, &iter, &eps)) {
        return NULL;
    }
    
    cHInitMat = convertPyMatToCMat(hMat, hNumOfVectors, hVectorLength);
    cNormMat = convertPyMatToCMat(normMat, normNumOfVectors, normVectorLength);

    finalHMat = createHMat(cHInitMat, cNormMat, iter, eps);
    freeMat(cHInitMat);
    freeMat(cNormMat);

    finalHNumOfVectors = symMat->cols;
    finalHVectorLength = symMat->rows;
    finalHVals = symMat->vals;
    
    pyMatrix = PyList_New(finalHNumOfVectors);  // Create a new Python list object for the rows

    if (pyMatrix) {
        for (int i = 0; i < finalHNumOfVectors; i++) {
            pyRow = PyList_New(finalHVectorLength);  // Create a new Python list object for each row
            if (pyRow) {
                for (int j = 0; j < finalHVectorLength; j++) {
                    pyValue = Py_BuildValue("d", finalHVals[i][j]);  // Convert C value to Python float
                    PyList_SET_ITEM(pyRow, j, pyValue);  // Set the value in the Python row list
                }
            }

            PyList_SET_ITEM(pyMatrix, i, pyRow);  // Set the row list in the Python matrix list
        }
    }

    return pyMatrix;
}


static PyMethodDef symnmfMethods[] = {
    {"sym",
      (PyCFunction) sym,
      METH_VARARGS,           
      PyDoc_STR("Calculate the symetric matrix of a set of data points")},
    {"ddg",
      (PyCFunction) ddg,
      METH_VARARGS,           
      PyDoc_STR("Calculate the diagonal degree matrix of a set of data points")},
    {"norm",
      (PyCFunction) norm,
      METH_VARARGS,           
      PyDoc_STR("Calculate the normalized similarity matrix of a set of data points")},
    {"symnmf",
      (PyCFunction) symnmf,
      METH_VARARGS,           
      PyDoc_STR("Calculate the optimized H matrix given the inialize one, norm matrix, max iteration and eps")},
    {NULL, NULL, 0, NULL}     
};

static struct PyModuleDef symnmfMethods = {
    PyModuleDef_HEAD_INIT,
    "symnmfssp",
    NULL, 
    -1,  
    symnmfMethods 
};

PyMODINIT_FUNC PyInit_symnmfssp(void)
{
    PyObject *m;
    m = PyModule_Create(&symnmfmodule);
    if (!m) {
        return NULL;
    }
    return m;
}
