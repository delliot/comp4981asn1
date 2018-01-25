#include "RDumbTerminal.h"


void input(int i_pipe[], int t_pipe[])
{
	char buffer[BUF_LEN];
	int i = 0;
	char c;

	clear_buf(buffer);

	close(i_pipe[0]);

	while ((c = getchar()))
	{
		switch (c)
		{
		case ASCII_CTRL_K:
			catch_signal(SIGABRT);
			break;
		case ASCII_ESC:
		case ASCII_CTRL_D:
		case ASCII_CTRL_X:
			break;
		case ASCII_ENTER:
			if(write(i_pipe[1], "\r\n", 2) < 0)
			{
				err_exit("error writing to regular output from input.c");
			}

			if(write(t_pipe[1], buffer, BUF_LEN) < 0)
			{
				err_exit("error writing to translate output from input.c");
			}
			clear_buf(buffer);
			i = 0;
			break;

		default:
			if(write(i_pipe[1], &c, 1) < 0)
			{
				err_exit("error writing to regular output from input.c"); 
			}

			if(i + 1 == BUF_LEN)
			{
				buffer[i++] = c;

				if(write(i_pipe[1], "\r\n", 2) < 0)
				{
					err_exit("error writing to regular output from input.c");
				}

				if(write(t_pipe[1], buffer, BUF_LEN) < 0)
				{
					err_exit("error writing to translate output from input.c");
				}
				clear_buf(buffer);
				i = 0;

			}
			else
			{
				buffer[i++] = c;
			}

		}
	}

}
