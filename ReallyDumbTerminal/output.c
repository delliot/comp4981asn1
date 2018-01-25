#include "RDumbTerminal.h"


void output(int input[2])
{
	char write_buf[BUF_LEN];
	size_t i;

	close(input[1]);
	
	int read_stat;

	clear_buf(write_buf);

	while(1)
	{
		switch(read_stat = read(input[0], write_buf, BUF_LEN))
		{
			case -1:
				err_exit("bad read from pipe");
				break;
			case 0:
				break;
			default:
				if(write(STDOUT_FILENO, write_buf, BUF_LEN) < 0)
				{
					err_exit("bad write to stadout");
				}

				clear_buf(write_buf);
				break;
		}

	}

}

void clear_buf(char * buf)
{
	size_t i;

	for(i = 0; i < BUF_LEN; i++)
	{
		buf[i] = '\0';
	}
}
