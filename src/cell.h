#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define SIZE 10

struct Cell
{
    int id;
    struct CellStatus *cell_status;
    struct CellRule *cell_rule;
    struct CellInput *cell_input;
};

struct CellStatusNode
{
    int status;
};

struct CellStatus
{
    int status; // 当前状态
    int status_size; // 状态数
    struct CellStatusNode *output_status_group;
    int status_default; // 默认开始状态
};

struct CellRule
{
    int rule_size; // 规则数
    struct CellRuleNode *rule_group; // 规则组
    int rule_default_status; // 默认规则
};

struct CellRuleNode
{
    int input_status;
    int output_status;
};

struct CellInput
{
    int input_size;
    int input_status_size;
    struct CellStatusNode *input_status_group; // 状态类型
    struct Cell *cell_group;
    int input_status_swap;
};

struct CellInputTransfer // 有没必要转换，因为每个独立状态对于元胞自动机都是独立的
{
    int default_status;
};

// print.c
int print_system_check();
void print_clear();
void print_cell_group(struct Cell *cell_group, int size);
void print_cell_total(struct Cell *cell_group, int size, char *name);
void print_cell(struct Cell cell);
void print_cell_all(struct Cell *cell_group, int size);
void print_cell_status(struct Cell *cell_group, int local);
void print_cell_status_all(struct Cell *cell_group, int size);

// cell_create.c
struct Cell *cell_init(int status, int status_size, struct CellStatusNode *output_status_group, int rule_size, struct CellRuleNode *rule_group, int input_size, int input_status_size, struct CellStatusNode *input_status_group, struct Cell *cell_group);
void cell_status_init(struct Cell *cell, int status, int status_size, struct CellStatusNode *output_status_group);
void cell_status_set(struct Cell *cell, int status, int status_size, struct CellStatusNode *output_status_group);
void cell_status_add(struct Cell *cell, struct CellStatusNode status_node);

void cell_rule_init(struct Cell *cell, int rule_size, struct CellRuleNode *rule_group);
void cell_rule_set(struct Cell *cell, int rule_size, struct CellRuleNode *rule_group);
void cell_rule_add(struct Cell *cell, struct CellRuleNode rule_node);

void cell_input_init(struct Cell *cell, int input_size, int input_status_size, struct CellStatusNode *input_status_group, struct Cell *cell_group);
void cell_input_set(struct Cell *cell, int input_size, int input_status_size, struct CellStatusNode *input_status_group, struct Cell *cell_group);
void cell_input_add(struct Cell *cell, struct CellStatusNode status_node);

void cell_free(struct Cell *cell);
void cell_free_all(struct Cell *cell, int cell_size);

// cell_calc.c
int calc_power(int base, int times);
int calc_cell_input_status(struct Cell *cell);
void calc_cell_status_get(struct Cell *cell);
int calc_cell_status_match(struct Cell *cell);
void calc_cell_status(struct Cell *cell);
void calc_cell_status_all(struct Cell *cell, int cell_size);

// cell_train.c
void cell_rule_train(struct Cell *cell, struct CellRuleNode *rule_group, int rule_size);
