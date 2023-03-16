/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-s <dlopez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 17:31:32 by dlopez-s          #+#    #+#             */
/*   Updated: 2023/03/16 15:12:56 by dlopez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	first_son(char *argv[])
{
	int		file1;

	file1 = open(argv[1], O_RDONLY, 0644);
	if (file1 < 0)
		exit(EXIT_FAILURE);
	dup2(file1, STDIN_FILENO);
	close(file1);
}

void	last_son(int argc, char *argv[], char *env[])
{
	int		file2;

	file2 = open(argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (file2 < 0)
		exit(EXIT_FAILURE);
	dup2(file2, STDOUT_FILENO);
	close(file2);
	exec_cmd(argv[argc - 2], env);
}

void	bonus_son(char *cmd, char *env[])
{
	pid_t	id;
	int		xtr[2];

	pipe(xtr);
	if (xtr < 0)
		exit (EXIT_FAILURE);
		
	id = fork(); //crea hijo i
	if (id < 0)
		exit(EXIT_FAILURE);
	if (id == 0)
	{
		dup2(xtr[1], STDOUT_FILENO);
		close(xtr[1]);
		exec_cmd(cmd, env);
	}
	else
	{
		close(xtr[1]);
		dup2(xtr[0], STDIN_FILENO);
		waitpid(id, 0, 0);
	}
	close(xtr[1]);
	close(xtr[0]);
}

/* pid_t data type stands for process identification and it is used to represent
process ids.  Whenever, we want to declare a variable that is going to be deal 
with the process ids we can use pid_t data type. The type of pid_t data is a 
signed integer type (signed int or we can say int). */

void	pipex(int argc, char *argv[], char *env[])
{
	int		i;

	i = 2;
	first_son(argv);
	while (i < argc - 2)
		bonus_son(argv[i++], env);
	last_son(argc, argv, env);
}

int	main(int argc, char *argv[], char *env[])
{
	if (argc >= 5)
	{
		//find_path_pos(env);
		// ft_putstr_fd("llega", 2);
		pipex(argc, argv, env);
		return (0);
	}
	// system("leaks pipex");
	return (1);
}
