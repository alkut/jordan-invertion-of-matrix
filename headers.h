#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <threads.h>
#include <pthread.h>

#define fail  -1
#define ok  0
#define machine_eps  2.20e-16

#define max_(i,j) (i<j ? j: i)
#define min_(i,j) (i<j ? i: j)

//-------input declaration--------------//
void input(double** , int , int );
double f(int , int , int , int );
int file_input(double** ,const char* , int );
//-------end of input declaration-------//


//-------matrix inventor declaration----//
typedef struct matrix_invertor
{
    double **initial, **ident;
    unsigned *perm;
    int n_;
    double *root1, *root2;
} matrix_invertor;
typedef struct thrd_arg
{
    matrix_invertor *inv_;
    int total_threads, cur_thread;
} thrd_arg;

int paralel(void*);
void synchronize(int);
int solve(double** , double** , int , matrix_invertor* , unsigned*, thrd_t*,thrd_arg*);
void invertor_constr(matrix_invertor*, double**, double**, int, unsigned*);
void invertor_destr(matrix_invertor*);
int jordan_invertion(matrix_invertor*, thrd_t*,thrd_arg*);
void raws_permutation(matrix_invertor *);
void copy_raws(matrix_invertor *, int , int);
void column_permutation(matrix_invertor *);
void copy_column(matrix_invertor *, int , int);
//-------end of matrix inventor declaration-//


//-------output declaration-------------//
void print_matrix(matrix_invertor*, int);
void print(double** , int , int, int);
//-------end of output declaration------//


//-------matrix operation declaration----//
double** create_matrix(int);
double** create_ident_matrix(int);
void clear_matrix(double **, double*);
void find_max(double **, int , int *, int *, int, int, int);
void swap_raws(double **, int, int);
void swap_columns(double **, int, int, int, int, int);
void second_transf(double **, int, double, int, int,int);
void third_transf(double **, int, int, double, int, int, int);
//-------end of matrix operation declaration-//

//-------matrix discrepancy declaration----//
double discrepancy(matrix_invertor*);
//-------end of matrix discrepancy declaration-//


//-------utility declaration---------------//
void swap(double*, double*);
void swapp(unsigned*, unsigned*);
void swappp(double**, double**);
//-------end of utility declaration--------//

