#include "cell.h"

struct Cell *cell_well()
{
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

struct Cell *cell_happy_angry()
{
    struct Cell *cell_happy_angry;
    int status = 0,
        status_size = 3,
        rule_size = 6,
        input_size = 1,
        input_status_size = 2,
        i;
    struct CellStatusNode *output_status_group, *input_status_group;
    output_status_group = malloc(sizeof(struct CellStatusNode) * status_size);
    for(i = 0; i < 3; i++)
    {
        output_status_group[i].status = i;
    }
    struct CellRuleNode *rule_group;
    rule_group = malloc(sizeof(struct CellRuleNode) * rule_size);
    for(i = 0; i < rule_size; i++)
    {
        rule_group[i].input_status = i;
    }
    rule_group[0].output_status = 0;
    rule_group[1].output_status = 0;
    rule_group[2].output_status = 1;
    rule_group[3].output_status = 1;
    rule_group[4].output_status = 2;
    rule_group[5].output_status = 2;
    struct Cell *cell_group;
    cell_group = malloc(sizeof(struct Cell*) * 2);
    cell_happy_angry = cell_init(status,
                                 status_size,
                                 output_status_group,
                                 rule_size,
                                 rule_group,
                                 input_size,
                                 input_status_size,
                                 input_status_group,
                                 cell_group);
    return cell_happy_angry;
}
