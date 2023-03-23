/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-s <dlopez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 17:31:32 by dlopez-s          #+#    #+#             */
/*   Updated: 2023/03/23 16:28:48 by dlopez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// static void	system_exec(char *cmdtemplate)
//  {
//          FILE* fp = popen(cmdtemplate, "r");
//          if (fp == NULL) {
//                  ft_putstr_fd("Error opening command", 2);
// 				 ft_putstr_fd(cmdtemplate, 2);
//                  return ;
//          }
//          char output[1024];
//          size_t n = fread(output, 1, sizeof(output), fp);
//          output[n] = '\0';
//          ft_putstr_fd(output, 2);
//  }
//
// static void exit_checks(void)
//  {
// 	char cmdtemplate[1024];
// 	ft_putstr_fd("\n\n******************************************\n", 2);
// 	ft_putstr_fd("Open fds:\n", 2);
// 	sprintf(cmdtemplate, "lsof -p %d | grep CHR", getpid());
// 	system_exec(cmdtemplate);
// 	ft_putstr_fd("\nLeaks:\n", 2);
// 	sprintf(cmdtemplate, "leaks %d", getpid());
// 	system_exec(cmdtemplate);
// 	ft_putstr_fd("******************************************\n", 2);
//  }

void	first_son(int *end, char *argv[], char *env[])
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
		close(end[0]);
		dup2(end[1], STDOUT_FILENO);
		close(end[1]);
		dup2(file1, STDIN_FILENO);
		close(file1);
		exec_cmd(command1, env);
	}
}

void	last_son(int *end, char *argv[], char *env[])
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
		close(end[1]);
		dup2(end[0], STDIN_FILENO);
		close(end[0]);
		dup2(file2, STDOUT_FILENO);
		close(file2);
		exec_cmd(command2, env);
	}
}

void	pipex(char	*argv[], char *env[])
{
	int		end[2];
	int		status;

	pipe(end);
	if (end < 0)
		exit (EXIT_FAILURE);
	first_son(end, argv, env);
	last_son(end, argv, env);
	close(end[0]);
	close(end[1]);
	waitpid(-1, &status, 0);
	waitpid(-1, &status, 0);
}

int	main(int argc, char *argv[], char *env[])
{
	// atexit(exit_checks);
	if (argc == 5)
		pipex(argv, env);
	else
		error_found("|invalid arguments| ");
}
