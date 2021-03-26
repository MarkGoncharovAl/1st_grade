//! @file Source.cpp
//! @mainpage Programm is used for square equations
//! - Source.cpp
//!@author Goncharov MA
//!@brief Use for solve square equations
 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
 
 
const int INFINITE = -1;    //using when we'll detect that our equation has infinite solutions
const int True = 1;
const int False = 0;
const int MAXTRIES = 100;     //using for trying to input something
const double precision = 0.000000001;     //using when we'll compare two double numbers
 
 
int Input (double* a, double* b, double* c);                                          // читает коэффициенты
int Solve_Sq_Equation (double a, double b, double c, double* ans1, double* ans2);
int Solve_Lin_Equation (double b, double c, double* ans1);
int Compare_Doubles (double num1, double num2);
void Print_Answer (int amount, double ans1, double ans2);
 
 
int main ()
{
 
    double a = NAN, b = NAN, c = NAN;
 
    printf ("# Programm \"Solve Equation\" has begun:\n");
    printf ("# Put coefficient of your square equation a, b, c using \"Enter\":\n");
 
    if (!Input(&a, &b, &c))
        return 1;
 
    double ans1 = NAN, ans2 = NAN;
    int AmountRoots = NAN;
 
    if (Compare_Doubles(a, 0))
    {
        AmountRoots = Solve_Lin_Equation (b, c, &ans1);
    }
    else
        AmountRoots = Solve_Sq_Equation (a, b, c, &ans1, &ans2);
 
    Print_Answer (AmountRoots, ans1, ans2);
 
    return 0;
}
 
/**
    int Input(double* a, double* b, double* c)
    ! It's reading coefficients of out equation
 
    !@param[out] a is head coeff
    !@param[out] b is middle coef
    !@param[out] c is free coef
    */
 
 
int Input (double* a, double* b, double* c)
{
    int chances = 0;
    char clean_buffer = '0';    //будет использоваться для очистки буфера
 
    printf ("Main coef: ");
    while ((scanf("%lg", a) == 0 || ((clean_buffer = getchar()) != '\n')) && chances < 100)
    {
        if (clean_buffer == ',')
            printf ("Use \".\" instead of \",\". ");
        while ((clean_buffer = getchar()) != '\n');   // позволяет очищать буфер, благодаря этому работает нормально scanf без fflush
 
        printf ("Try again. Put main coef: ");
        chances++;
    }
 
    printf ("Your main coeff was saved. Put middle coef: ");
    while ((scanf("%lg", b) == 0 || ((clean_buffer = getchar()) != '\n')) && chances < 100)
    {
        if (clean_buffer == ',')
            printf ("Use \".\" instead of \",\". ");
        while ((clean_buffer = getchar()) != '\n');
 
        printf ("Try again. Put middle coef: ");
        chances++;
    }
 
    printf ("Your middle coeff was saved. Put the smallest coef: ");
    while ((scanf("%lg", c) == 0 || ((clean_buffer = getchar()) != '\n')) && chances < 100)
    {
        if (clean_buffer == ',')
            printf ("Use \".\" instead of \",\". ");
        while ((clean_buffer = getchar()) != '\n');
 
        printf ("Try again. Put the smallest coef: ");
        chances++;
    }
 
    if (chances < 100)
    {
        printf ("\nThanks you, data was saved.\n");
        return True;
    }
    else
    {
        printf ("\nYou tried a lot, i think you're tired. You should go to the bedroom)");
        return False;
    }
}
 
/**
    int Solve_Lin_Equation(double b, double c, double* ans1)
    ! It's function for linary equation
 
    !@param[in] b is middle coef.
    !@param[in] c is free coef
    !@param[out] ans1 is the solution
    */
 
int Solve_Lin_Equation (double b, double c, double* ans1)
{
 
    if (Compare_Doubles(b, 0))
    {
        if (Compare_Doubles(c, 0))
            return INFINITE;
        else
            return 0;
    }
 
    else
    {
        *ans1 = -c / b;
        return 1;
    }
 
}
 
 
/**
    int Solve_Sq_Equation(double a, double b, double c, double* ans1, double* ans2)
    ! It's function for square equation
 
    !@param[in] a is the biggest coef.
    !@param[in] b is middle coef.
    !@param[in] c is free coef
    !@param[out] ans1 is the first solution
    !@param[out] ans2 is the second solution
    */
 
int Solve_Sq_Equation (double a, double b, double c, double* ans1, double* ans2)
{
 
    double SquareDisc = b * b - 4 * a * c;
 
    if (SquareDisc > 0)
    {
        *ans1 = (-b - sqrt (SquareDisc)) / (2 * a);
        *ans2 = (-b + sqrt (SquareDisc)) / (2 * a);
        return 2;
    }
 
    else if (Compare_Doubles (SquareDisc, 0))
    {
        *ans1 = -b / (2 * a);
        return 1;
    }
 
    else
        return 0;
 
}
 
/**
    int CompareZero(double num1, double num2)
    ! It's using for comparing two double numbers
    @param[in] num1 is the first comparing number
    @param[in] num2 is the second comparing number
    @param[out] true - numbers are equal
    @param[out] false - numbers aren't equal
    */
 
int Compare_Doubles (double num1, double num2)
{
    if (num1 - num2 > -1 * precision && num1 - num2 < precision)
        return True;
    else
        return False;
}
 
/**
    void Print_Answer(int AmountRoots, double ans1, double ans2)
    ! It's using for printing answer of our equation
    @param[in] AmountRoots is the amount of roots of our equation
    @param[in] ans1 is the first root
    @param[in] ans2 is the first root
    */
 
void Print_Answer (int AmountRoots, double ans1, double ans2)
{
    switch (AmountRoots)
    {
    case 0:
        printf ("\n\n# Your equation hasn't got roots\n\n");
        break;
 
    case 1:
        printf ("\n\n# Your equation has 1 solution %lg\n\n", ans1);
        break;
 
    case 2:
        printf ("\n\n# Your equation has 2 solutions %lg and %lg\n\n", ans1, ans2);
        break;
 
    case INFINITE:
        printf ("\n\n# Every real numer is the solution of your equation\n\n");
        break;
 
    default:
        printf ("\n\n# Programm has a crush - get visit the nearest programmist\n\n");
    }
}