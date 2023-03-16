/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-s <dlopez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 17:31:32 by dlopez-s          #+#    #+#             */
/*   Updated: 2023/03/16 18:10:43 by dlopez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	first_son(int *xtr, char *argv[], char *env[])
{
	pid_t	id;
	int		file1;
	char	*command1;

	command1 = argv[2];
	id = fork();
	if (id < 0)
		exit(EXIT_FAILURE);
	if (id == 0) //crea hijo 1
	{
		file1 = open(argv[1], O_RDONLY, 0644);
		if (file1 < 0)
			exit(EXIT_FAILURE);
		close(xtr[0]);
		dup2(xtr[1], STDOUT_FILENO);
		close(xtr[1]);
		dup2(file1, STDIN_FILENO);
		close(file1);
		if (exec_cmd(command1, env) == 0)
		{
			ft_putstr_fd("command not found\n", STDERR_FILENO);
			exit (127);
		}
	}
}

void	last_son(int *xtr, char *argv[], char *env[])
{
	pid_t	id;
	int		file2;
	char	*command2;

	command2 = argv[3];
	id = fork(); //crea hijo 2
	if (id < 0)
		exit(EXIT_FAILURE);
	if (id == 0)
	{
		// exit(127);
		file2 = open(argv[4], O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (file2 < 0)
			exit(EXIT_FAILURE);
		close(xtr[1]);
		dup2(xtr[0], STDIN_FILENO);
		close(xtr[0]);
		dup2(file2, STDOUT_FILENO);
		close(file2);
		if (exec_cmd(command2, env) == 0)
		{
			ft_putstr_fd("command not found\n", STDERR_FILENO);
			exit (EXIT_SUCCESS);
		}
	}
}

/* pid_t data type stands for process identification and it is used to represent
process ids.  Whenever, we want to declare a variable that is going to be deal 
with the process ids we can use pid_t data type. The type of pid_t data is a 
signed integer type (signed int or we can say int). */
void	pipex(char	*argv[], char *env[])
{
	int		xtr[2];
	int		status;

	pipe(xtr);
	if (xtr < 0)
		exit (EXIT_FAILURE);
	first_son(xtr, argv, env);
	last_son(xtr, argv, env);
	
	close(xtr[0]);
	close(xtr[1]);
	waitpid(-1, &status, 0);
	waitpid(-1, &status, 0);
}

int	main(int argc, char *argv[], char *env[])
{
	if (argc == 5)
	{
		pipex(argv, env);
		return (0);
	}
	// system("leaks pipex");
	return (1);
}
