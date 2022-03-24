#include "headers.h"

void input(double** x, int k, int n)
{
    for (int i=0; i<n; ++i)
    {
        for (int j=0; j<n; ++j)
        {
            x[i][j]=f(k,n,i+1,j+1);
        }
    }
}

double f(int k, int n, int i, int j)
{
    switch (k)
    {
        case 1:return (double)(n-max_(i,j)+1);
        case 2:return (double)(max_(i,j));
        case 3:return (double)abs(i-j);
        case 4:return 1.0/(double)(i+j-1);
        default: return 0.0;
    }
}

int file_input(double** x,const char* filename, int n)
{
    FILE *f=fopen(filename,"r");
    if (!f)
    {
        return fail;
    }
    for (int i=0; i<n; ++i)
    {
        for (int j=0; j<n; ++j)
        {
            if (fscanf(f,"%lf",&x[i][j])!=1)
            {
                fclose(f);
                return fail;
            }
        }
    }
    fclose(f);
    return ok;
}
