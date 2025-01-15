#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define N (16)
#define MAP_SIZE (256)

void print_line(int* line);

typedef struct entry_t entry_t;

struct entry_t {
    int w[N]; // key
    int count;
    entry_t* next;
};

entry_t* map[MAP_SIZE];
int l = 1;

int hash(int* key)
{
    unsigned int h = 0;
    while(*key)
    {
        h = ((h << 5) + h) + *key;
        key++;
    }
    return h % MAP_SIZE;
}

int is_prime(int n)
{
    if(n == 1)
    {
        return 0;
    }
    int max = (int) sqrt((double) n);

    for(int i = 2; i < max + 1; i++)
    {
        if((n % i) == 0)
        {
            return 0;
        }
    }
    return 1;
}

void handle_line(int* n)
{
    int key = hash(n);
    //if !exists add
    entry_t* map_entry = map[key];
    if(map_entry == NULL)
    {
        entry_t* e = calloc(1, sizeof(entry_t));
        memcpy(e->w, n, sizeof(int)*N);
        e->count = 1;
        map[key] = e;
    } else { //if exists check if key match
        while(map_entry != NULL)
        {
            if(!memcmp(map_entry->w, n, sizeof(int)*N))
            {
                printf("equal\n");
            }
            map_entry = map_entry->next;
        }
    }
    
}

void read_line(int* n)
{
    memset(n, 0, sizeof(int)*N);
    int c;
    int i = 0;
    while((c = getchar()) != '\n' && c != EOF)
    {
        n[i] = c;
        i++;
    }
    n[i] = '\0';
    l++;
}

void print_line(int* line)
{
    while(*line)
    {
        printf("%c", *line);
        line++;
    }
    printf("\n");
}

int main()
{
    // entry_t* map[MAP_SIZE];
    int* n = calloc(N, sizeof(int));
    while(1)
    {
        read_line(n);
        print_line(n);
        printf("%d\n", hash(n));
        handle_line(n);
    }
    // int* n2 = calloc(N, sizeof(int));
    // read_line(n);
    // read_line(n2);

    // if(!memcmp(n, n2, sizeof(int)*N))
    // {
    //     printf("equal\n");
    // }
    return 0;
}