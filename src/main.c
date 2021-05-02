#include "cell.h"

void cell_init_test();
int cell_scanf(struct Cell *cell_group);
void cell_rule_train(int *obj_rule, int obj_rule_size, struct Cell *cell_group);

int main() // TODO 输入多个scanf
{
    cell_init_test();

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
        /* cell_status_change(cell_group + local, status); */
        /* cell_rule_change(cell_group + local, rule); */
        /* print_cell(cell_group[local]); */
        return local;
    }
    return 0;
}

void cell_init_test() {
    int *rule_group;
    struct CellStatusNode *status_group;
    struct Cell *cell, *cell_group;
    status_group = malloc(sizeof(struct CellStatusNode));
    rule_group = malloc(sizeof(int));
    cell_group = malloc(sizeof(struct Cell));
    cell = cell_init(0, 0, status_group, 0, rule_group, 0, cell_group);

    print_cell_all(cell, 1);
    calc_cell_status_all(cell, 1);
    print_cell_all(cell, 1);

    cell_free(cell);
    free(cell_group);
    free(rule_group);
    free(status_group);

    return;
}

void cell_rule_train(int *obj_rule, int obj_rule_size, struct Cell *cell_group)
{}
