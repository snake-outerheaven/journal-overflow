#include <stddef.h>

typedef struct board Board;

Board *board_init(int);
int board_kill(Board *);

int move(Board *, size_t, size_t);
