void swap(double *x, double *y)
{
    double tmp=*x;
    *x=*y;
    *y=tmp;
}

void swapp(unsigned* x, unsigned* y)
{
    unsigned tmp=*x;
    *x=*y;
    *y=tmp;
}

void swappp(double** x, double **y)
{
    double *tmp= *x;
    *x=*y;
    *y=tmp;
}