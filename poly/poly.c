#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "error.h"
#include "poly.h"

void print_poly(poly_t* p);

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
        // printf("p->n: %d\n", p->n);
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
            if(p->n > 0)
            {
                p->n = p->n - 1;
            }
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
    int s = p->n * q->n;
    poly_t* res = calloc(1, sizeof(poly_t));
    res->coef = calloc(s, sizeof(int));
    res->exp = calloc(s, sizeof(int));

    for(int i = 0; i < p->n; i++)
    {
        for(int j = 0; j < q->n; j++)
        {
            res->coef[res->n] = p->coef[i] * q->coef[j];
            res->exp[res->n] = p->exp[i] + q->exp[j];
            res->n++;
        }
    }

    // Gather same exponents
    for(int i = 1; i < res->n; i++)
    {
        
        if(res->exp[i] == res->exp[i-1])
        {
            res->coef[i-1] += res->coef[i];
            res->coef[i] = 0;
            res->exp[i] = 0;
            continue;
        }
        
        if(res->exp[i] > res->exp[i-1])
        {
            for(int j = i - 2; j > 0; j--)
            {
                if(res->exp[j] == res->exp[i])
                {
                    res->coef[j] += res->coef[i];
                    res->coef[i] = 0;
                    res->exp[i] = 0;
                    break;
                }
            }
        }       
    }

    // Remove empty
    // Sort exponents'
    int e, c, ii;
    for(int i = 1; i < res->n; i++)
    {
        ii = i;
        // while((res->exp[ii] > res->exp[ii - 1]) && (ii > 0))
        while((ii > 0) && (res->exp[ii] > res->exp[ii - 1]))
        {
            //Swap
            e = res->exp[ii - 1];
            c = res->coef[ii - 1];
            res->exp[ii-1] = res->exp[ii];
            res->coef[ii-1] = res->coef[ii];
            res->exp[ii] = e;
            res->coef[ii] = c;
            ii--;
        }
    }
    return res;
}

void print_poly(poly_t* p)
{
    int c = p->coef[0];
    if(c != 1)
    {
        if(c < 0)
        {
            printf("- %d", abs(c));
        } else {
            printf("%d", c);
        }
    }

    int e = p->exp[0];
    if(e)
    {
        printf("x");
    }
    if(e > 1)
    {
        printf("^%d", e);
    }
    // printf(" ");

    // int c, e;
    for(int i = 1; i < p->n; i++)
    {
        c = p->coef[i];
        if(c)
        {
            c > 0 ? printf(" + %d", abs(c)) : printf(" - %d", abs(c));
            e = p->exp[i];
            if(e)
            {
                printf("x");
            }
            if(e > 1)
            {
                printf("^%d", e);
            }
            // // if(i < p->n - 1)
            // // {
            //     printf(" ");
            // // }
        }
    }
    printf("\n");
}

// void print_poly_o(poly_t* p)
// {
//     for(int i = 0; i < p->n; i++)
//     {
//         printf("coef: %d \n", p->coef[i]);
//         printf("exp: %d \n", p->exp[i]);
//     }
// }

// int main()
// {
//     poly_t* p, *q, *res;

//     p = new_poly_from_string("173x^469 + 75x^466 - 606x^408 + 154x^338 - 539x^334 + 713x^289 - 595x^286 - 712x^216 + 12x^161 - 77x^103 + 899x^10 - 301");
//     q = new_poly_from_string("893x^458 + 399x^377 - 290x^293 + 4x^213 - 951x^131 + 663x^128 - 675x^70 + 105x^3 + 4");
//     // p = new_poly_from_string("x^2 + x + 1");
//     // q = new_poly_from_string("-x + 1");
//     res = mul(p, q);
//     // print_poly(p);
//     // print_poly(q);
//     print_poly(res);
//     // print_poly_o(pq);
//     // printf("res->n = %d\n", pq->n);
//     // print_poly_o(p);
//     // print_poly_o(q);

//     free_poly(p);
//     free_poly(q);
//     free_poly(res);

//     return 0;
// }