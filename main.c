/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-s <dlopez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 17:31:32 by dlopez-s          #+#    #+#             */
/*   Updated: 2023/03/07 15:57:00 by dlopez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void    pipex(char	*argv[], int file2, char *env[])
{
	/* pid_t data type stands for process identification and it is used to represent process ids. 
	Whenever, we want to declare a variable that is going to be deal with the process ids we can use pid_t data type.
	The type of pid_t data is a signed integer type (signed int or we can say int). */
	pid_t	id;
	int		status;
	int		xtr[2];
	char	*command1 = argv[2];
	char	*command2 = argv[3];

	pipe(xtr);
	if (xtr < 0)
		return ;
	id = fork();
	if (id < 0)
		return ;
	if (id == 0) //crea hijo 1
	{
		// dup2(file1, STDIN_FILENO);
		close(xtr[0]);
		dup2(xtr[1], STDOUT_FILENO);
		close(xtr[1]);
		exec_cmd(command1, env);
	}
	else //vuelve al padre
	{
		close(xtr[1]);
		id = fork(); //crea hijo 2
		if (id < 0)
			return ;
		if (id == 0)
		{
			dup2(xtr[0], STDIN_FILENO);
			close(xtr[0]);
			dup2(file2, STDOUT_FILENO);
			exec_cmd(command2, env);
			
		}
		else
			close(xtr[0]);
	}
	wait(&status);
	wait(&status);
}

int main(int argc, char *argv[], char *env[])
{
	int	file1;
	int	file2;

	if (argc == 5)
	{
		file1 = open(argv[1], O_RDONLY | O_CREAT, 0666);
		file2 = open(argv[4], O_RDWR | O_CREAT | O_TRUNC, 0666);
		if (file1 < 0 || file2 < 0)
			return (1);
		pipex(argv, file2, env);
	}
	return (0);
}