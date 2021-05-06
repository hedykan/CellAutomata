#include "cell.h"

void cell_init_test();
int cell_scanf(struct Cell *cell_group);
void cell_rule_train(struct CellRuleNode *rule_group, int rule_size, struct Cell *cell);
void calc_rule_all(struct Cell *cell);
void calc_rule_select(int rule_size, int status_size, int rule_count, int status_count, struct CellRuleNode **cell_rule_all, struct CellRuleNode **cell_rule_group);

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
        /* cell_status_set(cell_group + local, status, cell_group[local].cell_status->status_size, cell_group[local].cell_status->status_group); */
        /* cell_rule_change(cell_group + local, rule); */
        /* print_cell(cell_group[local]); */
        print_cell(cell_group[local]);
        return local;
    }
    return 0;
}

void cell_init_test() {
    struct Cell *cell, *cell_group;
    struct CellStatusNode *input_status_group, *output_status_group;
    struct CellRuleNode *rule_group;
    cell_group = malloc(sizeof(struct Cell));
    input_status_group = malloc(sizeof(struct CellStatusNode) * 2);
    output_status_group = malloc(sizeof(struct CellStatusNode) * 2);
    rule_group = malloc(sizeof(struct CellRuleNode) * 2);

    input_status_group[0].status = 0;
    input_status_group[1].status = 1;
    output_status_group[0].status = 0;
    output_status_group[1].status = 1;

    rule_group[0].input_status = 0;
    rule_group[0].output_status = 1;
    rule_group[1].input_status = 1;
    rule_group[1].output_status = 0;

    cell = cell_init(0, 2, input_status_group, output_status_group, 2, rule_group, 1, cell_group);
    cell->id = 0;
    cell->cell_input->cell_group = cell;
    cell[0].cell_rule->rule_default_status = 0;

    print_cell_all(cell, 1);
    /*     calc_cell_status_all(cell, 1); */
    calc_rule_all(cell);

    cell_free(cell);
    free(cell_group);
    free(rule_group);
    free(input_status_group);
    free(output_status_group);

    return;
}

void cell_rule_train(struct CellRuleNode *rule_group, int rule_size, struct Cell *cell) {
    int i, j;
    for(j = 0; j < cell->cell_status->status_size; j++) { // 排列组合状态组和规则组

        for(i = 0; i < rule_size; i++) { // 遍历符合的规则
            cell->cell_input->cell_group[0].cell_status->status = rule_group[i].input_status;
            calc_cell_status(cell);
            if(cell->cell_status->status != rule_group[i].output_status)
                break;
            if(i == (rule_size - 1))
                return;
        }
    }
}

void calc_rule_all(struct Cell *cell) {
    int rule_size = cell->cell_rule->rule_size;
    int status_size = cell->cell_status->status_size;
    int i, j;
    struct CellRuleNode **cell_rule_all;
    cell_rule_all = malloc(sizeof(struct CellRuleNode *) * rule_size);
    for(i = 0; i < rule_size; i++) {
        cell_rule_all[i] = malloc(sizeof(struct CellRuleNode) * status_size);
        for(j = 0; j < status_size; j++) {
            cell_rule_all[i][j].input_status = cell->cell_rule->rule_group[i].input_status;
            cell_rule_all[i][j].output_status = cell->cell_status->output_status_group[j].status;
        }
    }
    printf("rule:%d, status:%d\n", rule_size, status_size);
    for(i = 0; i < rule_size; i++) {
        for(j = 0; j < rule_size; j++) {
            printf("%d -> %d ", cell_rule_all[i][j].input_status, cell_rule_all[i][j].output_status);
        }
        printf("\n");
    }

    struct CellRuleNode **cell_rule_group;
    cell_rule_group = malloc(sizeof(struct CellRuleNode *) * status_size);
    for(i = 0; i < status_size; i++) {
        cell_rule_group[i] = malloc(sizeof(struct CellRuleNode) * rule_size);
    }
    calc_rule_select(rule_size, status_size, 0, 0, cell_rule_all, cell_rule_group);
    /* for(i = 0; i < status_size; i++) { */
    /*     for(j = 0; j < rule_size; j++) { */
    /*         printf("%d,%d ", cell_rule_group[i][j].input_status, cell_rule_group[i][j].output_status); */
    /*     } */
    /*     printf("\n"); */
    /* } */
}

// cell_rule_group 先分配好
// cell_rule_group 是以
void calc_rule_select(int rule_size, int status_size, int rule_count, int status_count, struct CellRuleNode **cell_rule_all, struct CellRuleNode **cell_rule_group) {
    if(rule_count >= rule_size) {
        printf("\n");
        return;
    }
    printf("[%d,%d] ", rule_count, status_count);
    // cell_rule_group[status_count][rule_count] = cell_rule_all[rule_count][status_count];
    int i;
    for(i = 0; i < status_size; i++) {
        calc_rule_select(rule_size, status_size, ++rule_count, i, cell_rule_all, cell_rule_group);
    }
    return;
}
