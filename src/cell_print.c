#include"cell.h"

int print_system_check()
{
#ifdef linux
    return 1;
#endif
#ifdef _WIN32
    return 0;
#endif
}

void print_clear()
{
    if(print_system_check())
        system("clear");
    else
        system("cls");
}

void print_cell_group(struct Cell *cell_group, int size)
{
    print_clear();
    int i;
    for(i = 0; i < 10; i++)
        printf("\n");
    for(i = 0; i < size; i++)
        printf("%d", cell_group[i].cell_status->status);
    printf("\n");
}

void print_cell_total(struct Cell *cell_group, int size, char *name)
{
    int happy = 0, angry = 0, i;
    for(i = 0; i < size; i++)
        happy += cell_group[i].cell_status->status;
    printf("%s = %d\n", name, happy);
}

void print_cell(struct Cell *cell)
{
    int i, j;
    printf("cell_id: %d\n", cell->id);
    printf("status: %d\nrule_size: %d\ninput_size: %d\n", cell->cell_status->status, cell->cell_rule->rule_size, cell->cell_input->input_size);
    printf("status_group:{\n\tstatus_size: %d\n", cell->cell_status->status_size);
    for(i = 0; i < cell->cell_status->status_size; i++) {
        printf("\tstatus_group %d: %d\n", i, cell->cell_status->status_group[i]);
    }
    printf("}\n");

    printf("rule_group:{\n\trule_size: %d\n\trule_default_status: %d\n", cell->cell_rule->rule_size, cell->cell_rule->rule_default_status);
    for(i = 0; i < cell->cell_rule->rule_size; i++) {
        printf("\trule_group_%d: [", i);
        for(j = 0; j < cell->cell_input->input_size; j++) {
            if(j < (cell->cell_input->input_size - 1)) {
                printf("%d, ", cell->cell_rule->rule_group[i].input_status[j]);
            } else {
                printf("%d", cell->cell_rule->rule_group[i].input_status[j]);
            }
        }
        printf("] -> %d\n", cell->cell_rule->rule_group[i].output_status);
    }
    printf("}\n");

    printf("input_group:{\n");
    for(i = 0; i < cell->cell_input->input_size; i++)
        printf("\tinput_status_group %d: %d\n", i, cell->cell_input->input_group[i]->id);
    printf("}\n");
    printf("\n");
}

void print_cell_all(struct Cell **cell_group, int size)
{
    int i;
    for(i = 0; i < size; i++)
        print_cell(cell_group[i]);
}

void print_cell_status_all(struct Cell **cell_group, int size)
{
    int i;
    for(i = 0; i < size; i++)
        print_cell_status(cell_group[i]);
    printf("\n");
}

void print_cell_status(struct Cell *cell)
{
    printf("%d", cell->cell_status->status);
}
