#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include "sym.h"
#include "ddg.h"
#include "ncm.h"
#include "symnmfImp.h"
#include "utils.h"

typedef MAT (*MatFunction)(MAT*);


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

pyObject* convertcMatToPyMat(MAT* matrix){
    
    PyObject* pyMatrix;
    PyObject* pyRow;
    PyObject* pyValue;

    int matNumOfVectors, matHVectorLength;
    double** matVals;
    
    
    matNumOfVectors = matrix->cols;
    matHVectorLength = matrix->rows;
    matVals = matrix->vals;
    
    pyMatrix = PyList_New(matNumOfVectors);  // Create a new Python list object for the rows

    if (pyMatrix) {
        for (int i = 0; i < matNumOfVectors; i++) {
            pyRow = PyList_New(matHVectorLength);  // Create a new Python list object for each row
            if (pyRow) {
                for (int j = 0; j < matHVectorLength; j++) {
                    pyValue = Py_BuildValue("d", matVals[i][j]);  // Convert C value to Python float
                    PyList_SET_ITEM(pyRow, j, pyValue);  // Set the value in the Python row list
                }
            }

            PyList_SET_ITEM(pyMatrix, i, pyRow);  // Set the row list in the Python matrix list
        }
    }

    return pyMatrix;
}

pyObject* operate(pyObject* pyMat, int NumOfVectors, int VectorLength, MatFunction goal){
    MAT* cVectors;
    MAT* finalMat;
    
    cVectors = convertPyMatToCMat(pyMat, NumOfVectors, VectorLength);

    finalMat = goal(cVectors);
    freeMat(cVectors);

    return convertcMatToPyMat(finalMat);
}


//Methods
static PyObject* sym(PyObject *self, PyObject *args){
    
    pyObject* xVector;
    int xNumOfVectors, xVectorLength;

    if(!PyArg_ParseTuple(args, "Oii", &xVector, &xNumOfVectors, &xVectorLength)) {
        return NULL;
    }

    return operate(xVector, xNumOfVectors, xVectorLength, createSymMat);
}

static PyObject* ddg(PyObject *self, PyObject *args){
    
    pyObject* xVector;
    int xNumOfVectors, xVectorLength;

    if(!PyArg_ParseTuple(args, "Oii", &xVector, &xNumOfVectors, &xVectorLength)) {
        return NULL;
    }

    return operate(xVector, xNumOfVectors, xVectorLength, createDdgMat);
}

static PyObject* norm(PyObject *self, PyObject *args){
    
    pyObject* xVector;
    int xNumOfVectors, xVectorLength;

    MAT* cVectors;
    MAT* normMat;

    if(!PyArg_ParseTuple(args, "Oii", &xVector, &xNumOfVectors, &xVectorLength)) {
        return NULL;
    }
    
    return operate(xVector, xNumOfVectors, xVectorLength, createNsmMat);
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

    if(!PyArg_ParseTuple(args, "OOiiiiid", &hMat, &hNumOfVectors, &hVectorLength, &normMat, &normNumOfVectors, &normVectorLength, &iter, &eps)) {
        return NULL;
    }
    
    cHInitMat = convertPyMatToCMat(hMat, hNumOfVectors, hVectorLength);
    cNormMat = convertPyMatToCMat(normMat, normNumOfVectors, normVectorLength);

    finalHMat = createHMat(cHInitMat, cNormMat, iter, eps);
    freeMat(cHInitMat);
    freeMat(cNormMat);

    return convertcMatToPyMat(finalHMat);
}


//Create api
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
