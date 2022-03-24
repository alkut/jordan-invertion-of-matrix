#include "headers.h"
#include <time.h>


int main(int argc, char *argv[])
{
    int t,n,m,k;
    char* filename;
    switch (argc)
    {
        case 5: break;
        case 6:filename=argv[5];break;
        default: return -1;
    }
    t=atoi(argv[1]);
    n=atoi(argv[2]);
    m=atoi(argv[3]);
    k=atoi(argv[4]);
    if (n<1) return -4;
    double **x=create_matrix(n);
    if (argc==5)
    {
        if (k<1 || k>4)
        {
            clear_matrix(x,*x);
            return -2;
        }
        input(x,k,n);
    }
    else
    {
        if (k!=0)
        {
            clear_matrix(x,*x);
            return -3;
        }
        if (file_input(x, filename,n)!=ok)
        {
            clear_matrix(x,*x);
            printf("error reading file\n");
            return -4;
        }
    }
    double **ans= create_ident_matrix(n);
    matrix_invertor inv;
    struct timespec ts,te;
    timespec_get(&ts, TIME_UTC);
    unsigned *p = (unsigned*)malloc(n*sizeof(unsigned));
    thrd_t* tids = (thrd_t*)malloc(sizeof(thrd_t)*t);
    thrd_arg *thrdArg=(thrd_arg*)malloc(sizeof(thrd_arg)*t);
    thrdArg->total_threads=t;
    if (solve(x, ans, n, &inv, p, tids, thrdArg)!=ok)
    {
        invertor_destr(&inv);
        printf("error inverting matrix\n");
        return -5;
    }
    timespec_get(&te, TIME_UTC);
    if (argc==5)
    {
        input(inv.initial,k,n);
    }
    else
    {
        file_input(inv.initial,filename,n);
    }
    print_matrix(&inv, m);
    printf("elapsed time is %.2lf sec",((double)((te.tv_sec-ts.tv_sec)*1000000000+(te.tv_nsec-ts.tv_nsec)))/(double)1000000000);
    invertor_destr(&inv);
    free(tids);
    free(thrdArg);
    return 0;
}
