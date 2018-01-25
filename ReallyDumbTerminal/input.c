#include "RDumbTerminal.h"


void input(int i_pipe[], int t_pipe[])
{
	char buffer[BUF_LEN];
	int i = 0;
	char c;

	close(i_pipe[0]);

	while ((c = getc(stdin)))
	{
		switch (c)
		{
		case ASCII_CTRL_K:
			signal(getpid(), SIGTERM);
			break;
		case ASCII_ESC:
		case ASCII_CTRL_D:
		case ASCII_CTRL_X:
			break;
		case ASCII_T:
			graceful_exit();
		case ASCII_X:
			if ( i > 0 && i < BUF_LEN )
			{
				buffer[i] = '\0';
				i--;
			}
		default:
			write(i_pipe[1], c, 1);
		}
	}

}