#include "RDumbTerminal.h"


int main(void)
{
	int i_pipe[2];
	int t_pipe[2];

	system("stty raw igncr -echo");

	if (pipe(i_pipe) < 0)
	{
		err_exit("input pipe failed");
	}

	if (pipe(t_pipe) < 0)
	{
		err_exit("translate pipe failed");
	}

	if ((translate_p = fork()) == 0)
	{
		close(i_pipe[1]);
		/*
		...translate...
		*/
		translate(translate_p, t_pipe);
		
	} 
	else if (translate_p == -1)
	{
		
	}
	else
	{
		if ((output_p = fork()) == 0)
		{

			/*
			...output...
			*/
			close(t_pipe[1]);
			output(output_p, i_pipe, t_pipe);
		}
		else
		{
			input_p = getpid();
			/*
			...input...
			*/
			input(input_p, i_pipe);
		}
	}

}

void catch_signal(int sig)
{
	switch (sig)
	{
	/*
	TODO populate this
	*/

	case 6:
		break;
	case 15:
		break;
	}
}

void err_exit(const char * error)
{
	perror("error creating pipe");
	if (getpid() == input_p)
	{
		system("stty -raw -igncr echo");
	}
	kill(translate_p, SIGTERM);
	kill(output_p, SIGTERM);
	kill(getpid(), SIGTERM);
}

