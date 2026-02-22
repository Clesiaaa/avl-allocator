#include <stdio.h>
#include "include/talloc.h"
#include "include/tfree.h"

int main(void) 
{
    int *p = t_allocx(10 * sizeof(int));
    printf("%p\n", p);

    int *q = (int *)t_allocx(128 * sizeof(int));
    printf("%p\n", q);

    t_freex(p);
    t_freex(q);

    return 0;
}