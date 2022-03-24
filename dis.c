#include "headers.h"
double discrepancy(matrix_invertor* inv)
{
    int n=inv->n_;
    double res=0, tmp;
    for (int i=0; i<n; ++i)
    {
        for (int j=0; j<n; ++j)
        {
            tmp=0;
            for (int k=0; k<n; ++k)
            {
                tmp+=inv->initial[i][k]*inv->ident[k][j];
            }
            tmp-=(i==j)?(1.0):(0.0);
            tmp*=tmp;
            res+=tmp;
        }
    }
    return sqrt(res);
    return sqrt(res/(n*n));
}
