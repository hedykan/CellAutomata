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

void print_cell_group(struct Cell *Cell_group, int size)
{
    print_clear();
    for(int i = 0; i < 10; i++)
        printf("\n");
    for(int i = 0; i < size; i++)
        printf("%d", Cell_group[i].status);
    printf("\n");
}

void print_cell_total(struct Cell *Cell_group, int size, char *name)
{
    int happy = 0, angry = 0;
    for(int i = 0; i < size; i++)
        happy += Cell_group[i].status;
    printf("%s = %d\n", name, happy);
}

void print_cell(struct Cell cell)
{
    printf("cell_id: %d\n", cell.id);
    printf("status: %d\nrule_size: %d\ninput_size: %d\n", cell.status, cell.rule_size, cell.input_size);
    printf("status_group:{\n");
    for(int i = 0; i < cell.status_size; i++)
        printf("    status_group%d: %d\n", i, cell.status_group[i]);
    printf("}\n");

    printf("rule_group:{\n");
    for(int i = 0; i < cell.rule_size; i++)
        printf("    rule_group%d: %d\n", i, cell.rule_group[i]);
    printf("}\n");

    printf("input_group:{\n");
    for(int i = 0; i < cell.input_size; i++)
        printf("    input_group%d: %d\n", i, cell.input_group[i]);
    printf("}\n");
    printf("\n");
}

void print_cell_all(struct Cell *cell_group, int size)
{
    for(int i = 0; i < size; i++)
        print_cell(cell_group[i]);
}

void print_cell_status_all(struct Cell *cell_group, int size)
{
    for(int i = 0; i < size; i++)
        print_cell_status(cell_group, i);
    printf("\n");
}

void print_cell_status(struct Cell *cell_group, int local)
{
    printf("%d", cell_group[local].status);
}
