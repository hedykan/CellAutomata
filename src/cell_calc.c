#include "cell.h"
// 计算

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

//TODO 树型查询
// int calc_cell_input_status(struct Cell *cell) {
//     int i, status = 0, obj_status, base;
//     for(i = 0; i < cell->cell_input->input_size; i++) {
//         obj_status = cell->cell_input->cell_group[i].cell_status->status;
//         base = cell->cell_input->cell_group[i].cell_status->status_size;
//         status = status + obj_status * calc_power(base, i);
//     }
//     return status;
// }

// 获取输入状态
void calc_cell_status_get(struct Cell *cell) {
    int i;
    for(i = 0; i < cell->cell_input->input_size; i++) {
        // 获取输入元胞状态
        cell->cell_input->input_status_swap[i] = cell->cell_input->input_group[i]->cell_status->status;
    }
}

// 获取匹配的状态
int calc_cell_status_match(struct Cell *cell) {
    int i, j;
    for(i = 0; i < cell->cell_rule->rule_size; i++) {
        for(j = 0; j < cell->cell_input->input_size; j++) {
            if(cell->cell_input->input_status_swap[j] != cell->cell_rule->rule_group[i].input_status[j])
                break;
        }
        if(j == cell->cell_input->input_size) // 查找数和输入组数相同，即查找到合适的规则
            return cell->cell_rule->rule_group[i].output_status;
    }
    return cell->cell_rule->rule_default_status;
}

// 计算新的状态
void calc_cell_status(struct Cell *cell) {
    cell->cell_status->status = calc_cell_status_match(cell);
}

// 计算所有输入
void calc_cell_status_all(struct Cell **cell_group, int cell_size) {
    int i;
    // 先获取
    for(i = 0; i < cell_size; i++) {
        calc_cell_status_get(cell_group[i]);
    }
    // 再更新
    for(i = 0; i < cell_size; i++) {
        calc_cell_status(cell_group[i]);
    }
}

// 获取输入组的输入状态总数
int calc_cell_input_status_size(struct Cell *cell) {
    int i, sum = 1;
    for(i = 0; i < cell->cell_input->input_size; i++) {
        sum = sum * cell->cell_input->input_group[i]->cell_status->status_size;
    }
    return sum;
}