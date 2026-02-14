#include <stddef.h>

typedef struct board Board;

Board *init_board(int);
int kill_board(Board *);

int move(Board *, size_t, size_t);
