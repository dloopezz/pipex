/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-s <dlopez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 17:31:32 by dlopez-s          #+#    #+#             */
/*   Updated: 2023/03/02 17:12:55 by dlopez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void    pipex(char	*argv[], int file1, int file2, char *env[])
{
	/* pid_t data type stands for process identification and it is used to represent process ids. 
	Whenever, we want to declare a variable that is going to be deal with the process ids we can use pid_t data type.
	The type of pid_t data is a signed integer type (signed int or we can say int). */
	pid_t	son1;
	int		xtr[2];
	//char	*command1 = argv[2];
	//char	*command2 = argv[3];

	pipe(xtr);
	if (xtr < 0)
		return ;
	son1 = fork();
	if (son1 < 0)
		return ;
	if (son1 == 0) //hijo
	{
		close(xtr[0]);
		dup2(file1, STDIN_FILENO);
		dup2(xtr[1], STDOUT_FILENO);
		execve("/bin/ls", argv, env);
	}
	if (son1 > 0) 
	{
		close(xtr[1]);
		dup2(xtr[0], STDIN_FILENO);
		dup2(file2, STDOUT_FILENO);
		exec_cmd(argv[3], env);
		// execve("/usr/bin/wc", argv, env);
		// execve("/bin/pwd", 0, env);
	}
}

int main(int argc, char *argv[], char *env[])
{
	int	file1;
	int	file2;

	if (argc > 0)
	{
		file1 = open(argv[1], O_RDONLY | O_CREAT, 0666);
		file2 = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, 0666);
		if (file1 < 0 || file2 < 0)
			return (1);
		pipex(argv, file1, file2, env);
	}
	return (0);
}
