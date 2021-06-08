#include "cell.h"

void cell_init_test();
int cell_scanf(struct Cell *cell_group);
void cell_rule_train(struct Cell *cell, struct CellRuleNode *rule_group, int rule_size);
void calc_rule_all(struct Cell *cell, struct CellRuleNode **cell_rule_group);
void calc_rule_select(int rule_size, int status_size, int rule_count, struct CellRuleNode **cell_rule_all, struct CellRuleNode **cell_rule_group, struct CellRuleNode *cell_rule_road);
void print_group(struct CellRuleNode *rule_group, int rule_size);

// TODO 状态组的扩展
// TODO 输入输出类型转换
int main()
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
    int input_size, output_size, rule_size, i;
    cell_group = malloc(sizeof(struct Cell));
    input_status_group = malloc(sizeof(struct CellStatusNode) * 2);
    output_status_group = malloc(sizeof(struct CellStatusNode) * 2);
    rule_group = malloc(sizeof(struct CellRuleNode) * 2);

    input_size = 2;
    for(i = 0; i < input_size; i++) {
        input_status_group[i].status = i;
    }

    output_size = 2;
    for(i = 0; i < output_size; i++) {
        output_status_group[i].status = i;
    }

    rule_size = input_size;
    for(i = 0; i < rule_size; i++) {
        rule_group[i].input_status = i;
        rule_group[i].output_status = i;
    }

    cell = cell_init(0, output_size, output_status_group, rule_size, rule_group, 1, input_size, input_status_group, cell_group);
    cell->id = 0;
    cell->cell_input->cell_group = cell;
    cell[0].cell_rule->rule_default_status = 0;

    // 训练
    struct CellRuleNode *rule_group1;
    rule_group1 = malloc(sizeof(struct CellRuleNode) * 2);
    rule_group1[0].input_status = 0;
    rule_group1[0].output_status = 1;
    rule_group1[1].input_status = 1;
    rule_group1[1].output_status = 0;

    cell_rule_train(cell, rule_group1, 2);
    free(rule_group1);


    for(i = 0; i < 10; i++) {
        calc_cell_status_all(cell, 1);
        print_cell_total(cell, 1, "not");
    }

    struct CellStatusNode status_node;
    struct CellRuleNode rule_node;
    cell_status_add(cell, status_node);
    cell_rule_add(cell, rule_node);
    cell_input_add(cell, status_node);
    print_cell_all(cell, 1);

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
    calc_rule_all(cell, cell_rule_group);

    for(i = 0; i < (cell_status_size * cell_rule_size); i++) {
        for(k = 0; k < rule_size; k++) {
            cell->cell_rule->rule_group[k].input_status = cell_rule_group[i][k].input_status;
            cell->cell_rule->rule_group[k].output_status = cell_rule_group[i][k].output_status;
        }
        for(j = 0; j < rule_size; j++) {
            cell->cell_input->cell_group[0].cell_status->status = rule_group[j].input_status;
            calc_cell_status_all(cell, 1);
            printf("check: %d, %d\n", cell->cell_status->status, rule_group[j].output_status);
            if(cell->cell_status->status != rule_group[j].output_status) {
                printf("no, i=%d, j=%d\n\n", i, j);
                break;
            }
            if(j == (rule_size - 1)) {
                printf("ok, %d\n\n", j);
                goto end;
            }
        }
    }

end:  // 这里free会造成外面无法获取cell_rule
    for(i = 0; i < (cell_status_size * cell_rule_size); i++) {
        free(cell_rule_group[i]);
    }
    free(cell_rule_group);
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
    calc_rule_select(rule_size, status_size, 0, cell_rule_all, cell_rule_group, cell_rule_road);

    // free
    for(i = 0; i < rule_size; i++) {
        free(cell_rule_all[i]);
    }
    free(cell_rule_all);
    free(cell_rule_road);
}

void calc_rule_select(int rule_size, int status_size, int rule_count, struct CellRuleNode **cell_rule_all, struct CellRuleNode **cell_rule_group, struct CellRuleNode *cell_rule_road) {
    int i;
    if(rule_count >= rule_size) {
        // 在这把经历的路径保存
        int cell_count = 0;
        for(i = 0; i < rule_size; i++) {
            cell_count = cell_count + (cell_rule_road[i].output_status * calc_power(status_size, i));
        }
        for(i = 0; i < rule_size; i++){
            cell_rule_group[cell_count][i] = cell_rule_road[i];
        }
        return;
    }
    for(i = 0; i < status_size; i++) {
        cell_rule_road[rule_count] = cell_rule_all[rule_count][i];
        calc_rule_select(rule_size, status_size, rule_count + 1, cell_rule_all, cell_rule_group, cell_rule_road);
    }
    return;
}

void print_group(struct CellRuleNode *rule_group, int rule_size) {
    int i;
    for(i = 0; i < rule_size; i++) {
        printf("%d -> %d\n", rule_group[i].input_status, rule_group[i].output_status);
    }
}
