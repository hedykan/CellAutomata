#include "cell.h"

struct Cell *cell_test()
{
    struct Cell *cell;
    int *status_group;
    status_group = malloc(sizeof(int) * 2);
    status_group[0] = 0;
    status_group[1] = 1;

    cell = cell_fast_init(0, 2, status_group);
    cell_input_add(cell, cell);
    cell_input_add(cell, cell);
    cell_input_add(cell, cell);

    // create里分配rule_input_status
    int output_status_group[8] = {1, 0, 1, 1, 0, 0, 1, 0};
    cell_rule_fast_set(cell, output_status_group, 4);

    int i;
    for (i = 0; i < 3; i++)
    {
        print_cell_status(cell);
        calc_cell_status(cell);
    }
    print_cell_status(cell);
    cell_free(cell);
    return cell;
}

// 传感器元胞，可以任意改变其状态
// 用cell_status_change
struct Cell *cell_sensor(int size)
{
    int *status_group, i;
    status_group = malloc(sizeof(int) * size);
    for (i = 0; i < size; i++)
    {
        status_group[i] = i;
    }
    struct Cell *cell_sensor = cell_fast_init(status_group[0], size, status_group);
    return cell_sensor;
}

void cell_emotion_init()
{
    struct Cell **cell_group;
    cell_group = malloc(sizeof(struct Cell *) * 2);

    // 0为情感元胞，1为输入元胞
    cell_group[0] = cell_sensor(4);
    cell_group[1] = cell_sensor(4);

    cell_group[0]->id = 0;
    cell_group[1]->id = 1;

    // 第一个是状态，第二个是输入
    cell_input_add(cell_group[0], cell_group[0]);
    cell_input_add(cell_group[0], cell_group[1]);

    // 设置规则组
    int output_status_group[16] = {0, 1, 2, 3, 1, 1, 0, 2, 2, 0, 2, 3, 0, 0, 3, 3};
    cell_rule_fast_set(cell_group[0], output_status_group, 0);
    print_cell_all(cell_group, 2);
    cell_operate(cell_group, 2, 1, 0);

    cell_free_all(cell_group, 2);
}