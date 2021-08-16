#include "cell.h"

struct Cell *cell_test() {
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
    for(i = 0; i < 3; i++) {
        print_cell_status(cell);
        calc_cell_status(cell);
    }
    print_cell_status(cell);
    cell_free(cell);
    return cell;
}

struct Cell *cell_well() {
    int *status_group;
    status_group = malloc(sizeof(int) * 2);
    status_group[0] = 0;
    status_group[1] = 1;
    struct Cell *cell_well = cell_fast_init(0, 2, status_group);
    return cell_well;
}

struct Cell *cell_happy_angry() {
    int *status_group;
    status_group = malloc(sizeof(int) * 3);
    status_group[0] = 0;
    status_group[1] = 1;
    status_group[2] = 2;
    struct Cell *cell_happy_angry = cell_fast_init(0, 3, status_group);
    return cell_happy_angry;
}

void happy_cell_init() {
    struct Cell **cell_group;
    cell_group = malloc(sizeof(struct Cell *) * 2);
    cell_group[0] = cell_well();
    cell_group[1] = cell_happy_angry();
    cell_group[0]->id = 0;
    cell_group[1]->id = 1;
    cell_input_add(cell_group[1], cell_group[0]);
    cell_input_add(cell_group[1], cell_group[1]);

    int output_status_group[6] = {0, 0, 0, 1, 1, 1};
    cell_rule_fast_set(cell_group[1], output_status_group, 0);

    print_cell_all(cell_group, 2);

    cell_free_all(cell_group, 2);
}