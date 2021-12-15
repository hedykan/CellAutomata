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

struct CellStatus
{
    int status; // 当前状态
    int status_size; // 状态数
    int *status_group; // 总状态数组
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
    int *input_status;
    int output_status;
};

struct CellInput
{
    int input_size;
    struct Cell **input_group;
    int *input_status_swap; // 输入组状态缓冲，以保证同步更新，否则有些元胞更新后状态改变了
};

// print.c
int print_system_check();
void print_clear();
void print_cell_group(struct Cell *cell_group, int size);
void print_cell_total(struct Cell *cell_group, int size, char *name);
void print_cell(struct Cell *cell);
void print_cell_all(struct Cell **cell_group, int size);
void print_cell_status_all(struct Cell **cell_group, int size);
void print_cell_status(struct Cell *cell);

// cell_create.c
struct Cell *cell_init(int status, int status_size, int *status_group, int rule_size, struct CellRuleNode *rule_group, int input_size, struct Cell **input_group);
struct Cell *cell_fast_init(int status, int status_size, int *status_group);
void cell_status_init(struct Cell *cell, int status, int status_size, int *status_group);
void cell_status_set(struct Cell *cell, int status, int status_size, int *status_group);
void cell_status_add(struct Cell *cell, int status_group_node);

void cell_rule_init(struct Cell *cell, int rule_size, struct CellRuleNode *rule_group);
void cell_rule_set(struct Cell *cell, int rule_size, struct CellRuleNode *rule_group);
void cell_rule_add(struct Cell *cell, struct CellRuleNode rule_node);

void cell_input_init(struct Cell *cell, int input_size, struct Cell **input_group);
void cell_input_set(struct Cell *cell, int input_size, struct Cell **input_group);
void cell_input_add(struct Cell *cell, struct Cell *input_group_node);

void cell_status_free(struct Cell *cell);
void cell_rule_free(struct Cell *cell);
void cell_input_free(struct Cell *cell);
void cell_free(struct Cell *cell);
void cell_free_all(struct Cell **cell_group, int cell_size);

void cell_rule_fast_set(struct Cell *cell, int *output_status_group, int rule_default_status);
void cell_rule_output_set(struct CellRuleNode *rule_group, int rule_size, struct Cell **input_group, int input_size, int *output_status_group, int floor, int *end);
void cell_rule_input_set(struct CellRuleNode *rule_group, struct Cell **input_group, int sum, int status_mut, int floor);

// cell_calc.c
int calc_power(int base, int times);
// int calc_cell_input_status(struct Cell *cell);
void calc_cell_status_get(struct Cell *cell);
int calc_cell_status_match(struct Cell *cell);
void calc_cell_status(struct Cell *cell);
void calc_cell_status_all(struct Cell **cell_group, int cell_size);
int calc_cell_input_status_size(struct Cell *cell);

// cell_train.c
void cell_rule_train(struct Cell *cell, struct CellRuleNode *rule_group, int rule_size);

// cell_operate.c
void cell_operate(struct Cell **cell_group, int cell_size, int change_index, int show_index);
void cell_status_change(struct Cell *cell, int status);

// cell_init.c
struct Cell *cell_test();
void cell_emotion_init();