#include "cell.h"

struct Cell *cell_test() {
    struct Cell *cell;
    int status_group[2] = {0, 1};

    cell = cell_fast_init(0, 2, status_group);
    cell_input_add(cell, cell);
    cell_input_add(cell, cell);
    cell_input_add(cell, cell);

    // create里分配rule_input_status
    int output_status_group[8] = {1, 0, 1, 1, 0, 0, 1, 0};
    cell_rule_fast_set(cell, output_status_group, 4);
    return cell;
}

struct Cell *cell_well() {
    int status_group_1[2] = {0, 1};
    struct Cell *cell_well = cell_fast_init(0, 2, status_group_1);
    print_cell(cell_well);
    return cell_well;
}

struct Cell *cell_happy_angry() {
    int status_group_1[3] = {0, 1, 2};
    struct Cell *cell_happy_angry = cell_fast_init(0, 3, status_group_1);
    print_cell(cell_happy_angry);
    return cell_happy_angry;
}

void happy_cell_init() {
    struct Cell **cell_group;
    cell_group = malloc(sizeof(struct Cell *) * 2);
    cell_group[0] = cell_well();
    cell_group[1] = cell_happy_angry();
    cell_input_add(cell_group[1], cell_group[0]);
    cell_input_add(cell_group[1], cell_group[1]);

    cell_free_all(cell_group, 2);
}