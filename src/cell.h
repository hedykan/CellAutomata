#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define SIZE 10

struct Cell
{
    int id;
    int status; // cell当前状态
    int status_size; // cell拥有的状态数
    int *status_group; // cell拥有的具体状态组，为状态序列
    int rule_size; // cell拥有的规则数
    int *rule_group; // cell拥有的具体规则组，为规则序列
    int input_size; // cell接受的输入数
    int *input_group; // cell接受的具体输入的来源，为cell_id
    int input_transfer_status; // 输入状态转换器，有些输入来源状态需要转换
};

struct CellNew
{
    int id;
    struct CellStatus *cell_status;
    struct CellRule *cell_rule;
    struct CellInput *cell_input;
};

struct CellStatus
{
    int status;
    int status_size;
    int *status_group; // 按顺序排列
};

struct CellRule
{
    int rule_size;
    int *rule_group;
};

struct CellInput
{
    int input_size;
    struct CellNew *cell_group;
    int input_status_swap;
    int input_default_status;
};

struct CellInputTransfer // 有没必要转换，因为每个独立状态对于元胞自动机都是独立的
{
    int default_status;
};

// cell_func.c
// 初始化
void cell_init(struct Cell *cell, int cell_id, int status, int status_size, int *status_group, int rule_size, int rule, int input_size, int *input_group, int transfer_status);
void cell_rule_set(struct Cell *cell, int rule_size, int rule);
void cell_status_set(struct Cell *cell, int status, int status_size, int *status_group);
void cell_input_set(struct Cell *cell, int input_size, int *input_group);
void cell_transfer_status_set(struct Cell *cell, int transfer_status);
void cell_status_change(struct Cell *cell, int status);
void cell_rule_change(struct Cell *cell, int rule);
void cell_free(struct Cell *cell, int size);

int calc_status_transfer(struct Cell *cell, int status); // 状态转换函数
void calc_rule_group(struct Cell *cell, int rule, int rule_size); // 简易规则2规则组转换装置
void calc_cell(struct Cell *cell_group, int size);
int calc_cell_status(struct Cell *cell_group, int local);
int calc_power(int base, int times);
void copy_cell_value(struct Cell *cell_group, struct Cell *cell_group_arr, int size);

// print.c
int print_system_check();
void print_clear();
void print_cell_group(struct Cell *Cell, int size);
void print_cell_total(struct Cell *Cell_group, int size, char *name);
void print_cell(struct Cell cell);
void print_cell_all(struct Cell *cell_group, int size);
void print_cell_status(struct Cell *cell_group, int local);
void print_cell_status_all(struct Cell *cell_group, int size);
