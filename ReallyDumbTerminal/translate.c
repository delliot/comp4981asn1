#include "RDumbTerminal.h"

void translate(int i_pipe[2], int t_pipe[2])
{
	char in_buf[BUF_LEN];
	char out_buf[BUF_LEN];
	

	int read_stat;
	int i, cursor;
	int terminate = 0;


	while(1)
	{
		clear_buf(in_buf);
		clear_buf(out_buf);

		switch(read_stat = read(t_pipe[0], in_buf, BUF_LEN))
		{
			case -1:
				err_exit("translate read failed");
			case 0:
				break;
			default:
				cursor = 0;

				for(i = 0; i < BUF_LEN; i++)
				{
					switch(in_buf[i])
					{
						case ASCII_A:
							out_buf[cursor++] = 'z';
							break;
						case ASCII_X:
							out_buf[--cursor] = '\0';
							break;
						case ASCII_K:
							clear_buf(out_buf);
							cursor = 0;
							break;
						case ASCII_T:
							terminate = 1;
							break;
						default:
							out_buf[cursor++] = in_buf[i];

					}	
				}

				printf("get to translate");

				if (write(i_pipe[1], out_buf, BUF_LEN) < 0)
				{
					err_exit("writing to output from translate failed");
				}

				if(write(i_pipe[1], "\r\n", 2))
				{
					err_exit("writing to output from translate failed");
				}

				if(terminate)
				{
					kill(getpid(), SIGTERM);
				}

				break;
		}	


	}

}

