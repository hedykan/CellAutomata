#include <stdio.h>
#include <stdlib.h>
#define SIZE 10

struct Cell
{
    int id;
    int status; // cell当前状态
    int status_size; // cell拥有的状态数
    int status_group[2]; // cell拥有的具体状态组，为状态序列
    int rule_size; // cell拥有的规则数
    int rule_group[8]; // cell拥有的具体规则组，为规则序列
    int input_size; // cell接受的输入数
    int input_group[3]; // cell接受的具体输入的来源，为cell_id
    int input_transfer; // 输入状态转换器，有些输入来源状态需要转换
};

void cell_init(struct Cell *cell, int cell_id, int status, int rule_size, int rule, int input_size, int *input_group);
void calc_rule_group(struct Cell *cell, int rule, int rule_size); // 简易规则2规则组转换装置
void calc_cell(struct Cell *cell_group, int size);
int calc_cell_status(struct Cell *cell_group, int local);
int calc_power(int base, int times);
void copy_cell_value(struct Cell *cell_group, struct Cell *cell_group_arr, int size);
void print_cell(struct Cell cell);
void print_cell_all(struct Cell *cell_group, int size);
void print_cell_status(struct Cell *cell_group, int size);
