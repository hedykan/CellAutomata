#include "cell.h"

int cell_scanf(struct Cell *cell_group);
void cell_init_test(struct Cell *cell_group, int size, int rule_size, int rule);

int main() // TODO 输入多个scanf
{
    struct Cell cell_group1[SIZE], cell_group2[SIZE];
    cell_init_test(cell_group1, SIZE, 8, 110);
    cell_init_test(cell_group2, SIZE, 8, 64);
    print_cell_all(cell_group1, SIZE);
    print_cell_all(cell_group2, SIZE);
    int local = 0;
    local = cell_scanf(cell_group1);
    scanf("%*c");
    local = cell_scanf(cell_group2);
    while(1)
    {
        /* for(int i = 0; i < 10; i++) */
        /* { */
        /*     printf("calc: \n"); */
        /*     print_cell_status_all(cell_group, SIZE); */
        /*     printf("cell%d: ", local); */
        /*     print_cell_status(cell_group, local); */
        /*     printf("\n"); */
        /*     calc_cell(cell_group, SIZE); */
        /*     print_cell_status(cell_group, SIZE); */
        /* } */
        sleep(1);
        calc_cell(cell_group1, SIZE);
        calc_cell(cell_group2, SIZE);
        print_cell_status_all(cell_group1, SIZE);
        print_cell_status_all(cell_group2, SIZE);
        /* print_cell_group(cell_group1, SIZE); */
        print_cell_total(cell_group1, SIZE, "happy");
        print_cell_total(cell_group2, SIZE, "angry");
    }
    cell_free(cell_group1, SIZE);
    cell_free(cell_group2, SIZE);

    return 0;
}

int cell_scanf(struct Cell *cell_group)
{
    int local, status, rule;
    char c;
    printf("user> ");
    scanf("%c,%d,%d,%d", &c, &local, &status, &rule);
    if(c == 'a')
    {
        cell_status_change(cell_group + local, status);
        cell_rule_change(cell_group + local, rule);
        print_cell(cell_group[local]);
        return local;
    }
    return 0;
}

void cell_init_test(struct Cell *cell_group, int size, int rule_size, int rule)
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
        int transfer_status = 0;
        cell_init(&cell_group[i], i, status, status_size, status_group, rule_size, rule, input_size, input_group, transfer_status);
    }
}
