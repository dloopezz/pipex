#include "pipex.h"

void    pipex(char *argv[], int fd1, int fd2, char env[])
{
	/* pid_t data type stands for process identification and it is used to represent process ids. 
	Whenever, we want to declare a variable that is going to be deal with the process ids we can use pid_t data type.
	The type of pid_t data is a signed integer type (signed int or we can say int). */
	pid_t	son;
	int	xtr[2];

	pipe(xtr);
	if (xtr < 0)
		return (-1);
	son = fork();
	if (son < 0)
		return (-1);
	if (son == 0)
	{
		dup2(xtr[0], STDIN_FILENO);
		
	}
}

int main(int argc, char *argv[], char *env[])
{
	int	file1;
	int	file2;

	file1 = open(argv[1], O_RDONLY);
	file2 = open(argv[3], O_RDWR, O_CREAT, O_TRUNC, 0777);
	if (file1 < 0 || file2 < 0)
		return (1);
	pipex(argv, file1, file2, env);
	return (0);
}


	