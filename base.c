#include "headers.h"

void clear_matrix(double** x, double *root)
{
    free(root);
    free(x);
}


double** create_matrix(int n)
{
    double **x=(double**)malloc(n*sizeof(double*));
    double *buf=(double*)malloc(n*n*sizeof(double));
    for (int i=0; i<n; ++i)
    {
        x[i]=buf+i*n;
    }
    buf=NULL;
    return x;
}

double** create_ident_matrix(int n)
{
    double **x=create_matrix(n);
    for (int i=0; i<n; ++i)
    {
        for (int j=0; j<n; ++j)
        {
            x[i][j]=(i==j)?1.0:0.0;
        }
    }
    return x;
}

void find_max(double ** x, int pos, int *imax, int *jmax, int n, int st, int end)
{
    if (n<0 || pos<0 || pos>n)
    {
        printf("error find max\n");
        return;
    }
    double tmp_max=fabs(x[pos][pos]);
    *imax=*jmax=pos;
    for (int i=st; i<end; ++i)
    {
        for (int j=pos; j<n; ++j)
        {
            if (fabs(x[i][j]) > tmp_max)
            {
                *imax=i;
                *jmax=j;
                tmp_max=fabs(x[i][j]);
            }
        }
    }
}




void swap_raws(double **x, int raw1, int raw2)
{
    if (raw1==raw2) return;
    swappp(x+raw1, x+raw2);
}

void swap_columns(double **x, int col1, int col2, int n, int st, int end)
{
    if (n<0 || col1<0 || col2<0 || col1>n || col2>n)
    {
        printf("error swap columns\n");
        return;
    }
    if (col1==col2) return;
    for (int j=st; j<end; ++j)
    {
        swap(&x[j][col1],&x[j][col2]);
    }
}

void second_transf(double ** x, int raw, double coef, int n, int st, int end)
{
    if (n<0 || raw<0 || raw>n)
    {
        printf("error 2nd transf\n");
        return;
    }
    for (int j=st; j<end; ++j)
    {
        x[raw][j]*=coef;
    }
}

void third_transf(double **x, int raw1, int raw2 , double coef, int n, int st, int end)
{
    if (n<0 || raw1<0 || raw2<0 || raw1>n || raw2>n)
    {
        printf("error 3rd transf\n");
        return;
    }
    if (raw1==raw2) return;
    for (int j=st; j<end; ++j)
    {
        x[raw1][j]+=coef*x[raw2][j];
    }
}
