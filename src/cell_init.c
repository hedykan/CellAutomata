#include "cell.h"

struct Cell *cell_well() {
    struct Cell *cell_well;
    int status, status_size, rule_size, input_size, input_status_size;
    struct CellStatusNode *output_status_group, *input_status_group;
    struct CellRuleNode *rule_group;
    struct Cell *cell_group;
    cell_well = cell_init(status,
                          status_size,
                          output_status_group,
                          rule_size,
                          rule_group,
                          input_size,
                          input_status_size,
                          input_status_group,
                          cell_group);
    return cell_well;
}

struct Cell *cell_happy_angry() {
    struct Cell *cell_happy_angry;
    return cell_happy_angry;
}
