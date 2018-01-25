#include "RDumbTerminal.h"


/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: translate
--
-- DATE: January 24th 2018
--
-- REVISIONS:
--
-- DESIGNER: Delan Elliot
--
-- PROGRAMMER: Delan Elliot
--
-- INTERFACE: void translate(int i_pipe[2], int t_pipe[2])
--									i_pipe[2]: outputs translated buffer to this pipe.
--									t_pipe[2]: takes input on this pipe from the input process
--
-- RETURNS: void
--
-- NOTES:
-- This function performs all the translation and text handling. Also terminates the process when it encounters a 'T'
----------------------------------------------------------------------------------------------------------------------*/
void translate(int i_pipe[2], int t_pipe[2])
{
	char in_buf[BUF_LEN];
	char out_buf[BUF_LEN];

	close(t_pipe[1]);
	close(i_pipe[0]);

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
							if(cursor > 0)
							{
								out_buf[--cursor] = '\0';
							}
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

				if (write(i_pipe[1], out_buf, BUF_LEN) < 0)
				{
					err_exit("writing to output from translate failed");
				}

				if(write(i_pipe[1], "\r\n", 2) < 0)
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
