#include <stdio.h>
#include "cell.h"

int main()
{
    int cell[SIZE] = {0, 0, 0, 0};
    print_cell(cell, SIZE);
    for(int i = 0; i < 10; i++)
    {
        calc_cell(cell, SIZE);
        print_cell(cell, SIZE);
        printf("\n");
    }
    return 0;
}
