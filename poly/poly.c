#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "error.h"
#include "poly.h"

struct poly_t {
    int n;
    int* coef;
    int* exp;
};

poly_t* new_poly_from_string(const char* a)
{
    poly_t* p = calloc(1, sizeof(poly_t));
    int len = strlen(a);
    p->coef = calloc(len, sizeof(int)); // Could do len/2
    p->exp = calloc(len, sizeof(int)); // len/3 ?

    int c, i, minus;
    i = 0;
    minus = 0;

    // for (int i = 0; i < len; i++)
    while(i < len)
    {
        c = a[i];
        if(isdigit(c))
        {
            int n = 0;
            while(isdigit(c) && i < len)
            {
                n = (n*10) + (c - '0');
                i++;
                c = a[i];
            }
            if(minus)
            {
                n = -n;
            }
            p->coef[p->n] = n;
            // p->n = p->n + 1;
        }

        if(c == 'x')
        {
            if(p->coef[p->n] == 0)
            {
                p->coef[p->n] = 1;
            }

            i++;
            c = a[i];

            if(c == '^')
            {
                int e = 0;
                i++;
                c = a[i];
                while(isdigit(c) && i < len)
                {
                    e = (e*10) + (c - '0');
                    i++;
                    c = a[i];
                }
                p->exp[p->n] = e;
            } else {
                p->exp[p->n] = 1; // 0 if a constant.
            }
        }

        if(c == ' ')
        {
            p->n = p->n + 1;
        }

        if(c == '-')
        {
            minus = 1;
            p->n = p->n - 1;
        }

        if(c == '+')
        {
            minus = 0;
            p->n = p->n - 1;
        }

        if(c == '\0')
        {
            p->n = p->n + 1;
        } 
        i++;
    }
    return p;
}

void free_poly(poly_t* p)
{
    free(p->coef);
    free(p->exp);
    free(p);
}

poly_t* mul(poly_t* p, poly_t* q)
{
    int s = p->n + q->n;
    poly_t* res = calloc(1, sizeof(poly_t));
    res->coef = calloc(s, sizeof(int));
    res->exp = calloc(s, sizeof(int));

    for(int i = 0; i < p->n; i++)
    {
        for(int j = 0; j < q->n; j++)
        {
            res->coef[i] = p->coef[i] * q->coef[j];
            res->exp[i] = p->exp + q->exp[j];
        }
    }
    return res;
}

void print_poly(poly_t* p)
{
    
}

void print_poly_o(poly_t* p)
{
    for(int i = 0; i < p->n; i++)
    {
        printf("coef: %d \n", p->coef[i]);
        printf("exp: %d \n", p->exp[i]);
    }
}

int main()
{
    poly_t* p, *q;

    p = new_poly_from_string("2x^2 - 7x + 1");
    q = new_poly_from_string("2x^2 + 3x + 4");
    print_poly_o(p);
    print_poly_o(q);

    free_poly(p);
    free_poly(q);

    return 0;
}