#include "cell.h"
/* int calc_power(int base, int times); */
// 计算
// 先获取全部状态再计算，不然会有不同时更新的情况出现
// TODO 缓存状态

// 计算输入状态
int calc_power(int base, int times) {
    if(times != 0) {
        int output, i;
        output = base;
        for(i = 1; i < times; i++)
            output = output * base;
        return output;
    }
    return 1;
}

int calc_cell_input_status(struct Cell *cell) {
    int i, status = 0, obj_status, base;
    for(i = 0; i < cell->cell_input->input_size; i++) {
        obj_status = cell->cell_input->cell_group[i].cell_status->status;
        base = cell->cell_input->cell_group[i].cell_status->status_size;
        status = status + obj_status * calc_power(base, i);
    }
    return status;
}

// 获取输入状态
void calc_cell_status_get(struct Cell *cell) {
    cell->cell_input->input_status_swap = calc_cell_input_status(cell);
}

// 获取匹配的状态
int calc_cell_status_match(struct Cell *cell) {
    int i;
    for(i = 0; i < cell->cell_status->status_size; i++) {
        if(cell->cell_status->input_status_group[i].status == cell->cell_input->input_status_swap) {
            return cell->cell_rule->rule_group[i].output_status;
        }
    }
    return cell->cell_rule->rule_default_status;
}

// 计算新的状态
void calc_cell_status(struct Cell *cell) {
    cell->cell_status->status = calc_cell_status_match(cell);
}

// 计算所有输入
void calc_cell_status_all(struct Cell *cell, int cell_size) {
    int i;
    // 先获取
    for(i = 0; i < cell_size; i++) {
        calc_cell_status_get(cell + i);
    }
    // 再更新
    for(i = 0; i < cell_size; i++) {
        calc_cell_status(cell + i);
    }
}
