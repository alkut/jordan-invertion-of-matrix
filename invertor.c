#include "headers.h"

int solve(double** x, double** ans, int n, matrix_invertor* inv, unsigned* p, thrd_t* tids, thrd_arg * targs)
{
    invertor_constr(inv, x,ans,n,p);
    return jordan_invertion(inv, tids, targs);
}

void invertor_constr(matrix_invertor* inv, double**x, double** ans, int n, unsigned* p)
{
    inv->initial=x;
    inv->ident=ans;
    inv->perm=p;
    for (int i=0; i<n; ++i)
    {
        inv->perm[i]=i;
    }
    inv->n_=n;
    inv->root1=*inv->ident;
    inv->root2=*inv->initial;
}

void invertor_destr(matrix_invertor* inv)
{
    clear_matrix(inv->initial, inv->root1);
    clear_matrix(inv->ident, inv->root2);
    free(inv->perm);
}

void synchronize(int total_threads)
{
    static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    static pthread_cond_t condvar_in = PTHREAD_COND_INITIALIZER;
    static pthread_cond_t condvar_out = PTHREAD_COND_INITIALIZER;

    static int threads_in = 0;
    static int threads_out = 0;

    pthread_mutex_lock(&mutex);

    threads_in++;

    if (threads_in >= total_threads) {
        threads_out = 0;
        pthread_cond_broadcast(&condvar_in);
    } else {
        while (threads_in < total_threads)
            pthread_cond_wait(&condvar_in, &mutex);
    }

    threads_out++;

    if (threads_out >= total_threads) {
        threads_in = 0;
        pthread_cond_broadcast(&condvar_out);
    } else {
        while (threads_out < total_threads)
            pthread_cond_wait(&condvar_out, &mutex);
    }

    pthread_mutex_unlock(&mutex);
}

int paralel(void* args)
{
    thrd_arg* targs=args;
    int n=targs->inv_->n_;
    matrix_invertor *inv=targs->inv_;
    int pos=0;
    for (; pos<n-1; ++pos) {
        if (targs->cur_thread==0) {
            int i_, j_;
            find_max(inv->initial, pos, &i_, &j_, n, pos, n);
            swap_columns(inv->initial, pos, j_, n, 0, n);
            swap_columns(inv->ident, pos, j_, n, 0, n);
            swap_raws(inv->initial, pos, i_);
            swap_raws(inv->ident, pos, i_);
            swapp(&inv->perm[pos], &inv->perm[j_]);
            if (fabs(inv->initial[pos][pos]) < machine_eps) {
                printf("error divide by %lf\n", inv->initial[pos][pos]);
                return fail;
            }
            double coef = 1.0 / inv->initial[pos][pos];
            second_transf(inv->initial, pos, coef, n, pos, n);
            second_transf(inv->ident, pos, coef, n, 0, n);
        }
        synchronize(targs->total_threads);
        double coef;
        int fraw=(targs->cur_thread*n)/targs->total_threads;
        int lraw=((targs->cur_thread+1)*n)/targs->total_threads;

        for (int i=fraw; i<lraw; ++i)
        {
            if (i!=pos)
            {
                coef=-inv->initial[i][pos];
                third_transf(inv->initial,i,pos,coef,n,pos,n);
                third_transf(inv->ident,  i,pos,coef,n,0,n);
            }
        }
        synchronize(targs->total_threads);
    }
        pos=n-1;
        if (targs->cur_thread==0)
        {
            double coef = 1.0 / inv->initial[pos][pos];
            second_transf(inv->initial, pos, coef, n, pos, n);
            second_transf(inv->ident, pos, coef, n, 0, n);
        }
        synchronize(targs->total_threads);
        double coef;
        int fraw=(targs->cur_thread*n)/targs->total_threads;
        int lraw=((targs->cur_thread+1)*n)/targs->total_threads;

        for (int i=fraw; i<lraw; ++i)
        {
            if (i!=pos)
            {
                coef=-inv->initial[i][pos];
                third_transf(inv->initial,i,pos,coef,n,pos,n);
                third_transf(inv->ident,  i,pos,coef,n,0,n);
            }
        }
        synchronize(targs->total_threads);
        return ok;
}

int jordan_invertion(matrix_invertor* inv, thrd_t* tids ,thrd_arg* targs)
{
    int res;
    for (int i=0; i<targs->total_threads; ++i)
    {
        targs[i].cur_thread=i;
        targs[i].inv_=inv;
        targs[i].total_threads=targs->total_threads;
        thrd_create(tids+i,paralel,targs+i);
    }
    for (int i=0; i<targs->total_threads; ++i)
    {
        thrd_join(tids[i],&res);
        if (res!=ok)
        {
            return fail;
        }
    }
    raws_permutation(inv);
    column_permutation(inv);
    return ok;
}

void raws_permutation(matrix_invertor *inv)
{
    int n=inv->n_;
    for (int i=0; i<n; ++i)
    {
        copy_raws(inv, inv->perm[i],i);
    }
}

void copy_raws(matrix_invertor *inv, int raw_to, int raw_from)
{
    swappp(&inv->initial[raw_to],&inv->ident[raw_from]);
}
void column_permutation(matrix_invertor *inv)
{
    int n=inv->n_;
    for (int i=0; i<n; ++i)
    {
        copy_column(inv, inv->perm[i], i);
    }
}

void copy_column(matrix_invertor *inv, int column_to, int column_from) {
    int n = inv->n_;
    if (column_from < 0 || column_from > n || column_to < 0 || column_to > n) {
        printf("error copy columns\n");
        return;
    }
    for (int j = 0; j < n; ++j) {
        inv->ident[j][column_to] = inv->initial[j][column_from];
    }
}
