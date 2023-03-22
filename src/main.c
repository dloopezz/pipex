/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-s <dlopez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 17:31:32 by dlopez-s          #+#    #+#             */
/*   Updated: 2023/03/22 17:41:30 by dlopez-s         ###   ########.fr       */
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
	if (id == 0)
	{
		file1 = ft_open(argv[1], INFILE);
		close(xtr[0]);
		dup2(xtr[1], STDOUT_FILENO);
		close(xtr[1]);
		dup2(file1, STDIN_FILENO);
		close(file1);
		exec_cmd(command1, env);
	}
}

void	last_son(int *xtr, char *argv[], char *env[])
{
	pid_t	id;
	int		file2;
	char	*command2;

	command2 = argv[3];
	id = fork();
	if (id < 0)
		exit(EXIT_FAILURE);
	if (id == 0)
	{
		file2 = ft_open(argv[4], OUTFILE);
		close(xtr[1]);
		dup2(xtr[0], STDIN_FILENO);
		close(xtr[0]);
		dup2(file2, STDOUT_FILENO);
		close(file2);
		exec_cmd(command2, env);
	}
}

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
		pipex(argv, env);
	else
		return (1);
}
