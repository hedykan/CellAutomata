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
        cell_status_set(cell_group + local, status, cell_group[local].cell_status->status_size, cell_group[local].cell_status->status_group);
        /* cell_rule_change(cell_group + local, rule); */
        /* print_cell(cell_group[local]); */
        print_cell(cell_group[local]);
        return local;
    }
    return 0;
}

void cell_init_test() {
    struct Cell *cell, *cell_group;
    struct CellStatusNode *status_group;
    struct CellRuleNode *rule_group;
    cell_group = malloc(sizeof(struct Cell));
    status_group = malloc(sizeof(struct CellStatusNode) * 2);
    rule_group = malloc(sizeof(struct CellRuleNode) * 2);

    status_group[0].input_status = 0;
    status_group[1].input_status = 1;

    rule_group[0].input_status = 0;
    rule_group[0].output_status = 1;
    rule_group[1].input_status = 1;
    rule_group[1].output_status = 0;

    cell = cell_init(0, 2, status_group, 2, rule_group, 1, cell_group);
    cell->id = 0;
    cell->cell_input->cell_group = cell;
    cell[0].cell_rule->rule_default_status = 0;

    int i;
    for(i = 0; i < 10; i++) {
        print_cell_all(cell, 1);
        calc_cell_status_all(cell, 1);
    }

    cell_free(cell);
    free(cell_group);
    free(rule_group);
    free(status_group);

    return;
}

void cell_rule_train(int *obj_rule, int obj_rule_size, struct Cell *cell_group)
{}
