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

void print_cell(struct Cell cell)
{
    int i;
    printf("cell_id: %d\n", cell.id);
    printf("status: %d\nrule_size: %d\ninput_size: %d\n", cell.cell_status->status, cell.cell_rule->rule_size, cell.cell_input->input_size);
    printf("status_group:{\nstatus_size: %d\n", cell.cell_status->status_size);
    for(i = 0; i < cell.cell_status->status_size; i++) {
        printf("    output_status_group %d: %d\n", i, cell.cell_status->output_status_group[i].status);
    }
    printf("}\n");

    printf("rule_group:{\nrule_size: %d\nrule_default_status: %d\n", cell.cell_rule->rule_size, cell.cell_rule->rule_default_status);
    for(i = 0; i < cell.cell_rule->rule_size; i++)
        printf("    rule_group: %d -> %d\n", cell.cell_rule->rule_group[i].input_status, cell.cell_rule->rule_group[i].output_status);
    printf("}\n");

    printf("input_group:{\n");
    for(i = 0; i < cell.cell_input->input_status_size; i++)
        printf("    input_status_group %d: %d\n", i, cell.cell_input->input_status_group[i].status);
    for(i = 0; i < cell.cell_input->input_size; i++)
        printf("    input_group%d: %d\n", i, cell.cell_input->cell_group[i].id);
    printf("}\n");
    printf("\n");
}

void print_cell_all(struct Cell *cell_group, int size)
{
    int i;
    for(i = 0; i < size; i++)
        print_cell(cell_group[i]);
}

void print_cell_status_all(struct Cell *cell_group, int size)
{
    int i;
    for(i = 0; i < size; i++)
        print_cell_status(cell_group, i);
    printf("\n");
}

void print_cell_status(struct Cell *cell_group, int local)
{
    printf("%d", cell_group[local].cell_status->status);
}
