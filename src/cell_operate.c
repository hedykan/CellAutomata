#include "cell.h"

// TODO 把他改的普适起来
void cell_operate(struct Cell **cell_group, int cell_size, int change_index, int show_index)
{
    int status[5] = {1, 3, 2, 1, 2}, i;
    for (i = 0; i < 5; i++)
    {
        // 在这一时刻瞬间改变传感器的输入值
        cell_status_change(cell_group[change_index], status[i]);
        // 先获取状态
        calc_cell_status_get(cell_group[0]);
        calc_cell_status_get(cell_group[1]);
        // 进行运算
        calc_cell_status(cell_group[show_index]);
        printf("emotion_cell's input: %d, emotion_cell's status: ", status[i]);
        print_cell_status(cell_group[show_index]);
        printf("\n");
    }
}

void cell_status_change(struct Cell *cell, int status) {
    cell->cell_status->status = status;
}