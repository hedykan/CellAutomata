#include "cell.h"
struct CellNew *cell_init_new(int status, int status_size, int *status_group, int rule_size, int *rule_group, int input_size, struct CellNew *cell_group);
void cell_status_init(struct CellNew *cell, int status, int status_size, int *status_group);
void cell_rule_init(struct CellNew *cell, int rule_size, int *rule_group);
void cell_input_init(struct CellNew *cell, int input_size, struct CellNew *cell_group);
void cell_status_set_new(struct CellNew *cell, int status, int status_size, int *status_group);
void cell_rule_set_new(struct CellNew *cell, int rule_size, int *rule_group);
void cell_input_set_new(struct CellNew *cell, int input_size, struct CellNew *cell_group);
void cell_free_new(struct CellNew *cell);
void cell_free_all(struct CellNew *cell, int cell_size);
// 初始化函数

struct CellNew *cell_init_new(int status, int status_size, int *status_group, int rule_size, int *rule_group, int input_size, struct CellNew *cell_group) {
    struct CellNew *cell;
    cell = malloc(sizeof(struct CellNew));
    cell_status_init(cell, status, status_size, status_group);
    cell_rule_init(cell, rule_size, rule_group);
    cell_input_init(cell, input_size, cell_group);
    return cell;
}

void cell_status_init(struct CellNew *cell, int status, int status_size, int *status_group) {
    struct CellStatus *cell_status;
    cell_status = malloc(sizeof(struct CellStatus));
    cell->cell_status = cell_status;
    cell_status_set_new(cell, status, status_size, status_group);
}

void cell_status_set_new(struct CellNew *cell, int status, int status_size, int *status_group) {
    cell->cell_status->status = status;
    cell->cell_status->status_size = status_size;
    cell->cell_status->status_group = status_group;
}

void cell_rule_init(struct CellNew *cell, int rule_size, int *rule_group) {
    struct CellRule *cell_rule;
    cell_rule = malloc(sizeof(struct CellRule));
    cell->cell_rule = cell_rule;
    cell_rule_set_new(cell, rule_size, rule_group);
}

void cell_rule_set_new(struct CellNew *cell, int rule_size, int *rule_group) {
    cell->cell_rule->rule_size = rule_size;
    cell->cell_rule->rule_group = rule_group;
}

void cell_input_init(struct CellNew *cell, int input_size, struct CellNew *cell_group) {
    struct CellInput *cell_input;
    cell_input = malloc(sizeof(struct CellInput));
    cell->cell_input = cell_input;
    cell_input_set_new(cell, input_size, cell_group);
}

void cell_input_set_new(struct CellNew *cell, int input_size, struct CellNew *cell_group) {
    cell->cell_input->input_size = input_size;
    cell->cell_input->cell_group = cell_group;
}

void cell_free_new(struct CellNew *cell) {
    free(cell->cell_status);
    free(cell->cell_rule);
    free(cell->cell_input);
    free(cell);
}

void cell_free_all(struct CellNew *cell, int cell_size) {
    int i;
    for(i = 0; i < cell_size; i++) {
        cell_free_new(cell + i);
    }
}
