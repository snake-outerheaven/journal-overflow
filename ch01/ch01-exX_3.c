#include <unistd.h>

	/*
	 * getchar and putchar program in raw POSIX syscalls
	 */

int main()
{	
	char c;

	while(read(0, &c, 1) != 0)
		write(1, &c, 1);

	return 0;
}

	/*
	 * TODO: redo this program in x86 assembly.
	 */
