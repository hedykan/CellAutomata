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

struct CellRuleNode * cell_rule_group_set(int *status_group, int rule_size) {
    int i;
    struct CellRuleNode *rule_group;
    rule_group = malloc(sizeof(struct CellRuleNode) * rule_size);
    for(i = 0; i < rule_size; i++) {
        // 设置第i为的输入状态
        // 设置第i位的输出状态
        rule_group[i].output_status = status_group[i];
    }

    return rule_group;
}