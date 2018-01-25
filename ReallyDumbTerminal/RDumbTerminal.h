#pragma once

#include "signal.h"
#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"


#define ASCII_CTRL_K	0x0B
#define ASCII_A			0x61
#define ASCII_Z			0x7A
#define ASCII_ENTER		0x0D
#define ASCII_ESC		0x1B
#define ASCII_X			0x58
#define ASCII_K			0x4B
#define ASCII_T			0x74
#define ASCII_CTRL_X	0x38
#define ASCII_CTRL_D	0x24

#define BUF_LEN			255


void catch_signal(int sig);
void input(int i_pipe[], int t_pipe[]);
void graceful_exit();

pid_t input_p, output_p, translate_p;

int pipe_trans;
int pipe_input;




