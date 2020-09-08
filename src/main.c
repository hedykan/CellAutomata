#include <stdio.h>
#include "cell.h"
int main()
{
    struct Cell c[SIZE];
    c[0].status = 0;
    c[0].status_size = 8;
    for(int i = 0; i < 8; i++)
    {
        c[0].status_group[i] = 0;
    }
    printf("%d,%d,%d\n", c[0].status, c[0].status_size, c[0].status_group[1]);

    /* int cell[SIZE] = {0, 0, 0, 0}; */
    /* print_cell(cell, SIZE); */
    /* for(int i = 0; i < 10; i++) */
    /* { */
    /*     printf("\n"); */
    /*     calc_cell(cell, SIZE); */
    /*     print_cell(cell, SIZE); */
    /* } */

    return 0;
}
