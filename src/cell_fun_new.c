#include "cell.h"
void cell_status_set_new(struct CellNew *cell, int status, int status_size, int *status_group);

// 初始化函数
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
}

void cell_rule_set_new(struct CellNew *cell, int rule_size, int *rule_group) {
  cell->cell_rule->rule_size = rule_size;
  cell->cell_rule->rule_group = rule_group;
}
