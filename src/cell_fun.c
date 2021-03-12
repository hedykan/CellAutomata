#include <stdio.h>
#include "cell.h"

void cell_init(struct Cell *cell, int cell_id, int status, int status_size, int *status_group, int rule_size, int rule, int input_size, int *input_group, int transfer_status)
{
    cell->id = cell_id;
    cell_rule_set(cell, rule_size, rule);
    cell_status_set(cell, status, status_size, status_group);
    cell_input_set(cell, input_size, input_group);
    cell_transfer_status_set(cell, transfer_status);
}

void cell_rule_set(struct Cell *cell, int rule_size, int rule)
{
    cell->rule_size = rule_size;
    calc_rule_group(cell, rule, cell->rule_size);
}

void cell_status_set(struct Cell *cell, int status, int status_size, int *status_group)
{
    cell->status = status;
    cell->status_size = status_size;
    cell->status_group = status_group;
}

void cell_input_set(struct Cell *cell, int input_size, int *input_group)
{
    cell->input_size = input_size;
    cell->input_group = input_group;
}

void cell_transfer_status_set(struct Cell *cell, int transfer_status)
{
    cell->input_transfer_status = transfer_status;
}

void cell_status_change(struct Cell *cell, int status)
{
    cell->status = status;
}

void cell_rule_change(struct Cell *cell, int rule)
{
    calc_rule_group(cell, rule, cell->rule_size);
}

void cell_free(struct Cell *cell, int size)
{
    for(int i = 0; i < size; i++)
    {
        free(cell[i].status_group);
        free(cell[i].rule_group);
        free(cell[i].input_group);
    }
}

int calc_status_transfer(struct Cell *cell, int status)
{
    for(int i = 0; i < cell->status_size; i++)
    {
        if(cell->status_group[i] == status)
            return cell->status_group[i];
    }
    return cell->input_transfer_status;
}

void calc_rule_group(struct Cell *cell, int rule, int rule_size) // 简易规则2规则组转换装置
{
    int rule_swap = rule;
    int *rule_group = (int *)malloc(rule_size * sizeof(int));
    for(int i = (rule_size - 1); i >= 0; i--)
    {
        if((rule_swap - calc_power(2, i)) >= 0)
        {
            rule_group[i] = 1;
            rule_swap = rule_swap - calc_power(2, i);
        }
        else
            rule_group[i] = 0;
    }
    cell->rule_group = rule_group;
}

void calc_cell(struct Cell *cell_group, int size)
{
    struct Cell cell_group_arr[size];
    int num, status;
    copy_cell_value(cell_group, cell_group_arr, size); // 缓存细胞组
    for(int i = 0; i < size; i++) // 为每个cell计算状态
    {
        status = calc_cell_status(cell_group_arr, i);
        cell_status_change(cell_group + i, status);
    }
}

int calc_cell_status(struct Cell *cell_group, int local)
{
    int num = 0, i, status, input_status;
    for(i = 0; i < cell_group[local].input_size; i++) // 计算状态号
    {
        input_status = calc_status_transfer(cell_group + local, cell_group[cell_group[local].input_group[i]].status); // 输入状态转换
        num = (input_status * calc_power(2, i)) + num;
    }
    status = cell_group[local].rule_group[num];
    return status;
}

int calc_power(int base, int times)
{
    if(times != 0)
    {
        int output;
        output = base;
        for(int i = 1; i < times; i++)
            output = output * base;
        return output;
    }
    return 1;
}

void copy_cell_value(struct Cell *cell_group, struct Cell *cell_group_arr, int size)
{
    for(int i = 0; i < size; i++)
        cell_group_arr[i] = cell_group[i];
}

void print_cell(struct Cell cell)
{
    printf("cell_id: %d\n", cell.id);
    printf("status: %d\nrule_size: %d\ninput_size: %d\n", cell.status, cell.rule_size, cell.input_size);
    printf("status_group:{\n");
    for(int i = 0; i < cell.status_size; i++)
        printf("    status_group%d: %d\n", i, cell.status_group[i]);
    printf("}\n");

    printf("rule_group:{\n");
    for(int i = 0; i < cell.rule_size; i++)
        printf("    rule_group%d: %d\n", i, cell.rule_group[i]);
    printf("}\n");

    printf("input_group:{\n");
    for(int i = 0; i < cell.input_size; i++)
        printf("    input_group%d: %d\n", i, cell.input_group[i]);
    printf("}\n");
    printf("\n");
}

void print_cell_all(struct Cell *cell_group, int size)
{
    for(int i = 0; i < size; i++)
        print_cell(cell_group[i]);
}

void print_cell_status_all(struct Cell *cell_group, int size)
{
    for(int i = 0; i < size; i++)
        print_cell_status(cell_group, i);
    printf("\n");
}

void print_cell_status(struct Cell *cell_group, int local)
{
    printf("%d", cell_group[local].status);
}
