#include "cell.h"
void cell_scanf(struct Cell *cell_group);
void cell_init_test1(struct Cell *cell_group, int size);

int main()
{
    struct Cell cell_group[SIZE];
    cell_init_test1(cell_group, SIZE);
    int end;
    while(1)
    {
        print_cell_all(cell_group, SIZE);
        for(int i = 0; i < 10; i++)
        {
            printf("calc: \n");
            print_cell_status(cell_group, SIZE);
            calc_cell(cell_group, SIZE);
            /* print_cell_status(cell_group, SIZE); */
        }
        cell_scanf(cell_group);
    }
    cell_free(cell_group, SIZE);

    return 0;
}

void cell_scanf(struct Cell *cell_group)
{
    int input, local;
    int i = 0;
    printf("user> ");
    scanf("%d,%d", &local, &input);
    cell_status_change(cell_group + local, input);
}

void cell_init_test1(struct Cell *cell_group, int size)
{
    for(int i = 0; i < size; i++)
    {
        int num = -1, input_size = 3;
        int *input_group = (int *)malloc(input_size * sizeof(int));
        for(int j = 0; j < input_size; j++)
        {
            if((i + num) < 0)
                input_group[j] = size - 1;
            else if((i + num) > (size - 1))
                input_group[j] = 0;
            else
                input_group[j] = i + num;
            num++;
        }
        int status = 0, status_size = 2;
        int *status_group = (int *)malloc(2 * sizeof(int));
        status_group[0] = 0;
        status_group[1] = 1;
        int rule_size = 8;
        int rule = 110;
        cell_init(&cell_group[i], i, status, status_size, status_group, rule_size, rule, input_size, input_group);
    }
}
