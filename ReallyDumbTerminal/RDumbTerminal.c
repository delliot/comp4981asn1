#include "RDumbTerminal.h"


int main(void)
{
	int i_pipe[2];
	int t_pipe[2];

	signal(SIGABRT, catch_signal);
	signal(SIGTERM, catch_signal);

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
	
		/*
		...translate...
		*/
		translate(i_pipe, t_pipe);
		
	} 
	else if (translate_p == -1)
	{
		err_exit("translate fork failed");
	}
	else
	{
		if ((output_p = fork()) == 0)
		{

			/*
			...output...
			*/
			close(t_pipe[1]);
			output(i_pipe);
		}
		else
		{
			input_p = getpid();
			/*
			...input...
			*/
			input(i_pipe, t_pipe);
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
		signal(SIGABRT,NULL);

		if(getpid() == input_p)
		{
			system("stty -raw -igncr echo");	
		}
		kill(output_p, SIGABRT);
		kill(translate_p, SIGABRT);
		kill(getpid(), SIGABRT);

		break;
	case 15:
		signal(SIGTERM, NULL);
		if(getpid() == input_p)
		{
			system("stty -raw -igncr echo");
		}
		kill(output_p, SIGTERM);
		kill(translate_p, SIGTERM);
		kill(getpid(), SIGTERM);
		break;
	}
}

void err_exit(const char * error)
{
	perror(error);
	if (getpid() == input_p)
	{
		system("stty -raw -igncr echo");
	}
	kill(translate_p, SIGTERM);
	kill(output_p, SIGTERM);
	kill(getpid(), SIGTERM);
}

