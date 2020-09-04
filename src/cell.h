struct Rule
{
    int output[] = {0, 1, 0};
}

struct Cell
{
    int input;
    int output;
    int status;
    int status_group;
    struct Rule r1;
}
