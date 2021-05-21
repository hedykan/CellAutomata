#include "cell.h"
// 初始化函数

struct Cell *cell_init(int status, int status_size, struct CellStatusNode *output_status_group, int rule_size, struct CellRuleNode *rule_group, int input_size, int input_status_size, struct CellStatusNode *input_status_group, struct Cell *cell_group) {
    struct Cell *cell;
    cell = malloc(sizeof(struct Cell));
    cell_status_init(cell, status, status_size, output_status_group);
    cell_rule_init(cell, rule_size, rule_group);
    cell_input_init(cell, input_size, input_status_size, input_status_group, cell_group);
    return cell;
}

void cell_status_init(struct Cell *cell, int status, int status_size, struct CellStatusNode *output_status_group) {
    struct CellStatus *cell_status;
    cell_status = malloc(sizeof(struct CellStatus));
    cell->cell_status = cell_status;
    cell_status_set(cell, status, status_size, output_status_group);
}

void cell_status_set(struct Cell *cell, int status, int status_size, struct CellStatusNode *output_status_group) {
    cell->cell_status->status = status;
    cell->cell_status->status_size = status_size;
    cell->cell_status->output_status_group = output_status_group;
}

void cell_status_add(struct Cell *cell, struct CellStatusNode status_node) {
    int size = cell->cell_status->status_size;
    cell->cell_status->output_status_group = realloc(cell->cell_status->output_status_group, (sizeof(struct CellStatusNode) * (size + 1)));
    cell->cell_status->output_status_group[size] = status_node;
    cell->cell_status->status_size = size + 1;
}

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

void cell_input_init(struct Cell *cell, int input_size, int input_status_size, struct CellStatusNode *input_status_group, struct Cell *cell_group) {
    struct CellInput *cell_input;
    cell_input = malloc(sizeof(struct CellInput));
    cell->cell_input = cell_input;
    cell_input_set(cell, input_size, input_status_size, input_status_group, cell_group);
}

void cell_input_set(struct Cell *cell, int input_size, int input_status_size, struct CellStatusNode *input_status_group, struct Cell *cell_group) {
    cell->cell_input->input_size = input_size;
    cell->cell_input->input_status_size = input_status_size;
    cell->cell_input->input_status_group = input_status_group;
    cell->cell_input->cell_group = cell_group;
}

void cell_input_add(struct Cell *cell, struct CellStatusNode status_node) {
    int size = cell->cell_input->input_status_size;
    cell->cell_input->input_status_group = realloc(cell->cell_input->input_status_group, (sizeof(struct CellStatusNode) * (size + 1)));
    cell->cell_input->input_status_group[size] = status_node;
    cell->cell_input->input_status_size = size + 1;
}

void cell_free(struct Cell *cell) {
    free(cell->cell_status);
    free(cell->cell_rule);
    free(cell->cell_input);
    free(cell);
}

void cell_free_all(struct Cell *cell, int cell_size) {
    int i;
    for(i = 0; i < cell_size; i++) {
        cell_free(cell + i);
    }
}
