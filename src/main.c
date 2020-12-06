#include "cell.h"
void cell_init(struct Cell *cell_group);

int main()
{
    struct Cell cell_group[SIZE];
    cell_init(cell_group);
    print_cell_all(cell_group, SIZE);
    for(int i = 0; i < 10; i++)
    {
        calc_cell(cell_group, SIZE);
        printf("calc: \n");
        print_cell_status(cell_group, SIZE);
    }

    return 0;
}

void cell_init(struct Cell *cell_group)
{
    for(int i = 0; i < SIZE; i++)
    {
        cell_group[i].status = rand() % 2;
        cell_group[i].rule_size = 8;
        cell_group[i].input_size = 3;
        calc_rule_group(&cell_group[i], 110, cell_group[i].rule_size);
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
}
