#include "headers.h"

void print_matrix(matrix_invertor* inv, int m)
{
    int n=inv->n_;
    if (m==-1)
    {
        print(inv->ident, n,n,n);
        return;
    }
    if (m==0)
    {
        printf("discrepancy is %10.3e\n",discrepancy(inv));
        return;
    }
    if (m>n)
    {
        printf("error incorrect m more than n\n");
        return;
    }
    printf("initial matrix is:\n");
    print(inv->initial, n,n,m);
    printf("inverted matrix is:\n");
    print(inv->ident, n,n,m);
    printf("discrepancy is %10.3e\n",discrepancy(inv));
}

void print(double** x, int n, int k, int m)
{
    for (int i=0; i<min_(m,n); ++i)
    {
        for (int j=0; j<min_(m,k); ++j)
        {
            printf("%10.3e ",x[i][j]);
        }
        printf("\n");
    }
}