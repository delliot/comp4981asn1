#include "RDumbTerminal.h"

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: output
--
-- DATE: January 24th 2018
--
-- REVISIONS:
--
-- DESIGNER: Delan Elliot
--
-- PROGRAMMER: Delan Elliot
--
-- INTERFACE: void output(i_pipe[2])
--						i_pipe[]: the input.output pipe. Accessed by all 3 processes.
--
-- RETURNS: void
--
-- NOTES:
-- Output receives data from the 2 other processes and prints it to console. Does not do any processing.
----------------------------------------------------------------------------------------------------------------------*/
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


/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: clear_buf
--
-- DATE: January 24th 2018
--
-- REVISIONS:
--
-- DESIGNER: Delan Elliot
--
-- PROGRAMMER: Delan Elliot
--
-- INTERFACE: void clear_buf(char * buf)
--									char * buf: buffer to clear
--
-- RETURNS: void
--
-- NOTES:
-- Zeroes out a given buffer. All buffers are statically sized so no size parameter is needed.
----------------------------------------------------------------------------------------------------------------------*/
void clear_buf(char * buf)
{
	size_t i;

	for(i = 0; i < BUF_LEN; i++)
	{
		buf[i] = '\0';
	}
}
