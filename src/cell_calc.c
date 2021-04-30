#include "cell.h"

// 计算
// 先获取全部状态再计算，不然会有不同时更新的情况出现
// TODO 缓存状态
void calc_cell_status_get(struct CellNew *cell) {
    int i;
    for(i = 0; i < cell->cell_input->input_size; i++) {

    }
}
