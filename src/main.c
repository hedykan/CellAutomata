#include "cell.h"

void cell_init_test();
int cell_scanf(struct Cell *cell_group);
void cell_rule_train(struct Cell *cell, struct CellRuleNode *rule_group, int rule_size);
void calc_rule_all(struct Cell *cell, struct CellRuleNode **cell_rule_group);
void calc_rule_select(int rule_size, int status_size, int rule_count, int status_count, struct CellRuleNode **cell_rule_all, struct CellRuleNode **cell_rule_group, struct CellRuleNode *cell_rule_road);

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

    cell_rule_train(cell, rule_group, 2);

    cell_free(cell);
    free(cell_group);
    free(rule_group);
    free(input_status_group);
    free(output_status_group);

    return;
}

void cell_rule_train(struct Cell *cell, struct CellRuleNode *rule_group, int rule_size) {
    struct CellRuleNode **cell_rule_group;
    int cell_status_size = cell->cell_status->status_size;
    int cell_rule_size = cell->cell_rule->rule_size;
    cell_rule_group = malloc(sizeof(struct CellRuleNode *) * (cell_status_size * cell_rule_size));
    int i, j, k;
    for(i = 0; i < (cell_status_size * cell_rule_size); i++) {
        cell_rule_group[i] = malloc(sizeof(struct CellRuleNode) * cell_rule_size);
    }
    // 获取所有规则
    // TODO 获得的cell_rule_group只有status_size, 实际需要status_size * rule_size
    calc_rule_all(cell, cell_rule_group);

    for(i = 0; i < (cell_status_size * cell_rule_size); i++) {
        cell->cell_rule->rule_group = cell_rule_group[i];
        for(j = 0; j < rule_size; j++) {
            cell->cell_input->cell_group[0].cell_status->status = rule_group[j].input_status;
            calc_cell_status_all(cell, 1);
            // TODO 检验训练成功否
            /* print_cell_all(cell, 1); */
            printf("check: %d, %d\n", cell->cell_status->status, rule_group[j].output_status);
            if(cell->cell_status->status != rule_group[j].output_status) {
                printf("no, i=%d, j=%d\n\n", i, j);
                break;
            }
            if(j == (rule_size - 1)) {
                printf("ok, %d\n", j);
                for(k = 0; k < cell_rule_size; k++) {
                    printf("%d -> %d ", cell->cell_rule->rule_group[k].input_status, cell->cell_rule->rule_group[k].output_status);
                }
                goto end;
            }
        }
    }

end:
    for(i = (cell_status_size * cell_rule_size); i > 0; i--) {
        free(cell_rule_group + i);
    }
    return;
}

void calc_rule_all(struct Cell *cell, struct CellRuleNode **cell_rule_group) {
    int rule_size = cell->cell_rule->rule_size;
    int status_size = cell->cell_status->status_size;
    int i, j;
    struct CellRuleNode **cell_rule_all;
    cell_rule_all = malloc(sizeof(struct CellRuleNode *) * rule_size);
    
    // 获取所有组合
    for(i = 0; i < rule_size; i++) {
        cell_rule_all[i] = malloc(sizeof(struct CellRuleNode) * status_size);
        for(j = 0; j < status_size; j++) {
            cell_rule_all[i][j].input_status = cell->cell_rule->rule_group[i].input_status;
            cell_rule_all[i][j].output_status = cell->cell_status->output_status_group[j].status;
        }
    }

    // 排列组合所有情况
    struct CellRuleNode *cell_rule_road;
    cell_rule_road = malloc(sizeof(struct CellRuleNode) * rule_size);
    calc_rule_select(rule_size, status_size, 0, 0, cell_rule_all, cell_rule_group, cell_rule_road);

    // free
    for(i = rule_size; i > 0; i--) {
        for(j = status_size; j > 0; j--) {
            free(cell_rule_all[i] + j);
        }
        free(cell_rule_all + i);
    }
    for(i = rule_size; i > 0; i--) {
        free(cell_rule_road + i);
    }
}

void calc_rule_select(int rule_size, int status_size, int rule_count, int status_count, struct CellRuleNode **cell_rule_all, struct CellRuleNode **cell_rule_group, struct CellRuleNode *cell_rule_road) {
    if(rule_count >= rule_size) {
        // 在这把经历的路径保存
        // TODO 这里cell_rule_group的索引需要status_size * 2 + rule_size
        int i, cell_count = 0;
        for(i = 0; i < rule_size; i++) {
            cell_count = cell_count + (cell_rule_road[i].output_status * calc_power(status_size, i));
        }
        for(i = 0; i < rule_size; i++){
            /* printf("[%d -> %d] ", cell_rule_road[i].input_status, cell_rule_road[i].output_status); */
            cell_rule_group[cell_count][i] = cell_rule_road[i];
        }
        return;
    }
    int i;
    for(i = 0; i < status_size; i++) {
        cell_rule_road[rule_count] = cell_rule_all[rule_count][i];
        calc_rule_select(rule_size, status_size, rule_count + 1, i, cell_rule_all, cell_rule_group, cell_rule_road);
    }
    return;
}
