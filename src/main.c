#include <stdio.h>
#include "cell.h"
int main()
{
    struct Cell cell_group[SIZE];
    for(int i = 0; i < SIZE; i++)
    {
        cell_group[i].status = 0;
        cell_group[i].rule_size = 8;
        cell_group[i].input_size = 3;
        /* calc_rule_group(cell_group[i], 110, 8); */
        for(int j = 0; j < cell_group[i].rule_size; j++)
            cell_group[i].rule_group[j] = ((j + 1) % 2);
        int num = -1;
        for(int j = 0; j < cell_group[i].input_size; j++)
        {
            if((i + num) < 0)
                cell_group[i].input_group[j] = SIZE - 1;
            else if((i + num) > (SIZE - 1))
                cell_group[i].input_group[j] = 0;
            else
                cell_group[i].input_group[j] = i + num;
            num++;
        }
    }
    print_cell_all(cell_group, SIZE);
    for(int i = 0; i < 10; i++)
    {
        calc_cell(cell_group, SIZE);
        printf("calc: \n");
        print_cell_status(cell_group, SIZE);
    }

    /* calc_cell(cell, SIZE); */
    /* print_cell(cell, SIZE); */
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
