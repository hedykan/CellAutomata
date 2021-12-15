#include "cell.h"

void cell_init_test();
int cell_scanf(struct Cell *cell_group);
void print_group(struct CellRuleNode *rule_group, int rule_size);

// TODO 创建传感器
// 传感器是一个元胞，但是他的状态可以随意修改
int main() {
    cell_init_test();

    return 0;
}

void cell_init_test() {
    // happy_cell_init();
    cell_emotion_init();
}

int cell_scanf(struct Cell *cell_group) {
    int local, status, rule;
    char c;
    printf("user> ");
    scanf("%c,%d,%d,%d", &c, &local, &status, &rule);
    if(c == 'a')
    {
        /* cell_status_change(cell_group + local, status); */
        /* cell_status_set(cell_group + local, status, cell_group[local].cell_status->status_size, cell_group[local].cell_status->status_group); */
        /* cell_rule_change(cell_group + local, rule); */
        /* print_cell(cell_group[local]); */
        // print_cell(cell_group[local]);
        return local;
    }
    return 0;
}

void print_group(struct CellRuleNode *rule_group, int rule_size) {
    int i;
    for(i = 0; i < rule_size; i++) {
        printf("%d -> %d\n", rule_group[i].input_status, rule_group[i].output_status);
    }
}
