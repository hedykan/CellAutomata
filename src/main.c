#include "cell.h"

void cell_init_test();
int cell_scanf(struct Cell *cell_group);
void print_group(struct CellRuleNode *rule_group, int rule_size);

// TODO 状态组的扩展
// TODO 输入输出类型转换
int main()
{
    cell_init_test();

    return 0;
}

void cell_init_test() {
    struct Cell *cell, *input_group;
    int status, status_size, *status_group, rule_size, input_size;
    struct CellRuleNode *rule_group;
    status = 0;
    status_size = 1;
    status_group = malloc(sizeof(int) * status_size);
    status_group[0] = 0;
    
    input_size = 2;
    input_group = malloc(sizeof(struct Cell) * input_size);

    rule_size = 1;
    rule_group = malloc(sizeof(struct CellRuleNode) * rule_size);
    rule_group[0].input_status = malloc(sizeof(int) * input_size);
    rule_group[0].input_status[0] = 0;
    rule_group[0].input_status[1] = 0;
    rule_group[0].output_status = 0;

    cell = cell_init(status, status_size, status_group, rule_size, rule_group, input_size, input_group);
    input_group[0] = cell[0];
    input_group[1] = cell[0];
    cell->cell_input->input_group = input_group;

    print_cell(cell[0]);
    calc_cell_status_all(cell, 1);
    print_cell(cell[0]);

    free(rule_group[0].input_status);
    free(rule_group);
    cell_free_all(cell, 1);
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

// void cell_init_test() {
//     struct Cell *cell, *cell_group;
//     struct CellStatusNode *input_status_group, *output_status_group;
//     struct CellRuleNode *rule_group;
//     int input_size, output_size, rule_size, i;
//     cell_group = malloc(sizeof(struct Cell));
//     input_status_group = malloc(sizeof(struct CellStatusNode) * 2);
//     output_status_group = malloc(sizeof(struct CellStatusNode) * 2);
//     rule_group = malloc(sizeof(struct CellRuleNode) * 2);

//     input_size = 2;
//     for(i = 0; i < input_size; i++) {
//         input_status_group[i].status = i;
//     }

//     output_size = 2;
//     for(i = 0; i < output_size; i++) {
//         output_status_group[i].status = i;
//     }

//     rule_size = input_size;
//     for(i = 0; i < rule_size; i++) {
//         rule_group[i].input_status = i;
//         rule_group[i].output_status = i;
//     }

//     cell = cell_init(0, output_size, output_status_group, rule_size, rule_group, 1, input_size, input_status_group, cell_group);
//     cell->id = 0;
//     cell->cell_input->cell_group = cell;
//     cell[0].cell_rule->rule_default_status = 0;

//     // 训练
//     struct CellRuleNode *rule_group1;
//     rule_group1 = malloc(sizeof(struct CellRuleNode) * 2);
//     rule_group1[0].input_status = 0;
//     rule_group1[0].output_status = 1;
//     rule_group1[1].input_status = 1;
//     rule_group1[1].output_status = 0;

//     cell_rule_train(cell, rule_group1, 2);
//     free(rule_group1);


//     for(i = 0; i < 10; i++) {
//         calc_cell_status_all(cell, 1);
//         print_cell_total(cell, 1, "not");
//     }

//     // 新增测试
//     struct CellStatusNode status_node;
//     struct CellRuleNode rule_node;
//     cell_status_add(cell, status_node);
//     cell_rule_add(cell, rule_node);
//     cell_input_add(cell, status_node);
//     print_cell_all(cell, 1);

//     cell_free(cell);
//     free(cell_group);
//     free(rule_group);
//     free(input_status_group);
//     free(output_status_group);

//     return;
// }

void print_group(struct CellRuleNode *rule_group, int rule_size) {
    int i;
    for(i = 0; i < rule_size; i++) {
        printf("%d -> %d\n", rule_group[i].input_status, rule_group[i].output_status);
    }
}
