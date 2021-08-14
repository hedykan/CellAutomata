#include "cell.h"
// 初始化函数
struct Cell *cell_init(int status, int status_size, int *status_group, int rule_size, struct CellRuleNode *rule_group, int input_size, struct Cell *input_group) {
    struct Cell *cell;
    cell = malloc(sizeof(struct Cell));
    // 初始化状态组
    cell_status_init(cell, status, status_size, status_group);
    // 初始化输入组
    cell_input_init(cell, input_size, input_group);
    // 初始化规则组
    cell_rule_init(cell, rule_size, rule_group);

    return cell;
}

struct Cell *cell_fast_init() {
    struct Cell *cell, *input_group;
    int status, status_size, *status_group, rule_size, input_size;
    struct CellRuleNode *rule_group;
    cell = cell_init(status, status_size, status_group, rule_size, rule_group, input_size, input_group);
    return cell;
}

// 状态组设置
void cell_status_init(struct Cell *cell, int status, int status_size, int *status_group) {
    struct CellStatus *cell_status;
    cell_status = malloc(sizeof(struct CellStatus));
    cell->cell_status = cell_status;
    cell_status_set(cell, status, status_size, status_group);
}

void cell_status_set(struct Cell *cell, int status, int status_size, int *status_group) {
    cell->cell_status->status = status;
    cell->cell_status->status_size = status_size;
    cell->cell_status->status_group = status_group;
}

void cell_status_add(struct Cell *cell, int status_group_node) {
    int size = cell->cell_status->status_size;
    cell->cell_status->status_group = realloc(cell->cell_status->status_group, (sizeof(int) * (size + 1)));
    cell->cell_status->status_group[size] = status_group_node;
    cell->cell_status->status_size = size + 1;
}

// 规则组设置
void cell_rule_init(struct Cell *cell, int rule_size, struct CellRuleNode *rule_group) {
    struct CellRule *cell_rule;
    cell_rule = malloc(sizeof(struct CellRule));
    cell->cell_rule = cell_rule;
    cell_rule_set(cell, rule_size, rule_group);
}

void cell_rule_set(struct Cell *cell, int rule_size, struct CellRuleNode *rule_group) {
    cell->cell_rule->rule_size = rule_size;
    cell->cell_rule->rule_group = rule_group;
}

void cell_rule_add(struct Cell *cell, struct CellRuleNode rule_node) {
    int size = cell->cell_rule->rule_size;
    cell->cell_rule->rule_group = realloc(cell->cell_rule->rule_group, (sizeof(struct CellRuleNode) * (size + 1)));
    cell->cell_rule->rule_group[size] = rule_node;
    cell->cell_rule->rule_size = size + 1;
}

// 输入组设置
void cell_input_init(struct Cell *cell, int input_size, struct Cell *input_group) {
    struct CellInput *cell_input;
    cell_input = malloc(sizeof(struct CellInput));
    cell->cell_input = cell_input;
    cell->cell_input->input_status_swap = malloc(sizeof(int) * input_size);
    cell_input_set(cell, input_size, input_group);
}

void cell_input_set(struct Cell *cell, int input_size, struct Cell *input_group) {
    cell->cell_input->input_size = input_size;
    cell->cell_input->input_group = input_group;
}

// 新增输入节点
void cell_input_add(struct Cell *cell, struct Cell input_group_node) {
    int size = cell->cell_input->input_size;
    cell->cell_input->input_group = realloc(cell->cell_input->input_group, (sizeof(struct Cell) * (size + 1)));
    cell->cell_input->input_group[size] = input_group_node;
    cell->cell_input->input_size = size + 1;
}

void cell_free(struct Cell *cell) {
    free(cell->cell_status);
    free(cell->cell_rule);
    free(cell->cell_input->input_status_swap);
    free(cell->cell_input);
    free(cell);
}

void cell_free_all(struct Cell *cell, int cell_size) {
    int i;
    for(i = 0; i < cell_size; i++) {
        cell_free(cell + i);
    }
}

// 规则组快速设置
void cell_rule_fast_set(struct Cell *cell, int *output_status_group) {
    int sum;
    sum = calc_cell_input_status_size(cell);
    int *end;
    end = malloc(sizeof(int) * 1);
    *end = 0;
    cell_rule_output_set(cell->cell_rule->rule_group, cell->cell_rule->rule_size, cell->cell_input->input_group, cell->cell_input->input_size, output_status_group, 0, end);
    cell_rule_input_set(cell->cell_rule->rule_group, cell->cell_input->input_group, sum, cell->cell_input->input_group->cell_status->status_size, (cell->cell_input->input_size - 1));
    free(end);
}

// 只设置output
// 树状遍历到底部后设置输出组output
void cell_rule_output_set(struct CellRuleNode *rule_group, int rule_size, struct Cell *input_group, int input_size, int *output_status_group, int floor, int *end) {
    int i;
    // DOWN 如何知道第几次到达floor底部，添加end指针传递
    for(i = 0; i < input_group[floor].cell_status->status_size; i++) { // 遍历状态数
        if(floor < (input_size - 1)) { // floor 应该是输入数而不是状态数
            cell_rule_output_set(rule_group, rule_size, input_group, input_size, output_status_group, (floor + 1), end);
        } else {
            rule_group[*end].output_status = output_status_group[*end];
            *end = *end + 1;
        }
    }
    return;
}

// 只设置input
// 通过状态数组合status_size_sum算出状态组遍历次数all_mut，并通过状态数组合status_size_sum和状态数算出单个状态重复数status_mut
// 递归执行
void cell_rule_input_set(struct CellRuleNode *rule_group, struct Cell *input_group, int sum, int status_size_sum, int floor) {
    int i, j, k, status_size = input_group[floor].cell_status->status_size;
    // 计算每个状态重复次数
    int all_mut = sum / status_size_sum;
    // 计算状态遍历共需要几次
    int status_mut = status_size_sum / status_size;

    // 遍历总重复次数
    for(i = 0; i < all_mut; i++) {
        // 遍历所有状态
        for(j = 0; j < status_size; j++) {
            // 计算每个状态重复几次
            for(k = 0; k < status_mut; k++) {
                // 规则组的(i*status_size_sum+j)位赋值状态组第i位
                rule_group[(i * status_mut * status_size) + (j * status_mut) + k].input_status[floor] = input_group[floor].cell_status->status_group[j];
            }
        }
    }
    if(floor > 0) {
        cell_rule_input_set(rule_group, input_group, sum, (status_size_sum * input_group[floor].cell_status->status_size), (floor - 1));
    }
}