#pragma once
#include "readData.h"
#include "symnmfImp.h"

typedef MAT* (*MatFunction)(MAT*);

MAT* executeOperate(MatFunction, MAT*);
MAT* executeSymnmf(MAT*, MAT*, int, double);


