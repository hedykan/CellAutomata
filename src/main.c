#include "cell.h"
void cell_init_test(struct Cell *cell_group);

int main()
{
    struct Cell cell_group[SIZE];
    cell_init_test(cell_group);
    print_cell_all(cell_group, SIZE);
    for(int i = 0; i < 10; i++)
    {
        calc_cell(cell_group, SIZE);
        printf("calc: \n");
        print_cell_status(cell_group, SIZE);
    }

    return 0;
}

void cell_init_test(struct Cell *cell_group)
{
    for(int i = 0; i < SIZE; i++)
    {
        int num = -1, input_size = 3;
        int input_group[input_size];
        for(int j = 0; j < input_size; j++)
        {
            if((i + num) < 0)
                input_group[j] = SIZE - 1;
            else if((i + num) > (SIZE - 1))
                input_group[j] = 0;
            else
                input_group[j] = i + num;
            num++;
        }
        for(int j = 0; j < input_size; j++)
            printf("%d", input_group[i]);
        cell_init(&cell_group[i], i, (rand() % 2), 8, 110, input_size, input_group);
    }
}
