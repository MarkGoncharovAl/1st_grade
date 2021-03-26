#pragma once

const double APROX = 0.1;

enum class Type {Empty = 0, Num, Var, Op}; 


//registers - variables
const int COUNT_VALUE = 4;

const double VALUE_X1 = (const double)0;
const double VALUE_X2 = (const double)1;
const double VALUE_X3 = (const double)2;
const double VALUE_X4 = (const double)3;



const double OP_EMPTY = 0.0;
const double OP_ADD = 1.0;
const double OP_SUB = 2.0;
const double OP_MULT = 3.0;
const double OP_DIV = 4.0;
const double OP_DEG = 5.0;
const double OP_SIN = 6.0;
const double OP_COS = 7.0;