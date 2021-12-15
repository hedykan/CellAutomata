#include "cell.h"

// TODO 把他改的普适起来
void cell_operate(struct Cell **cell_group, int cell_size, int change_index, int show_index)
{
    int status;
    while(1)
    {
        // 在这一时刻瞬间改变传感器的输入值
        printf("please type an input:");
        scanf("%d", &status);
        cell_status_change(cell_group[change_index], status);
        // 先获取状态
        calc_cell_status_get(cell_group[0]);
        calc_cell_status_get(cell_group[1]);
        // 进行运算
        calc_cell_status(cell_group[show_index]);
        printf("emotion_cell's input: %d, emotion_cell's status: ", status);
        print_cell_status(cell_group[show_index]);
        printf("\n");
    }
}

void cell_status_change(struct Cell *cell, int status) {
    cell->cell_status->status = status;
}