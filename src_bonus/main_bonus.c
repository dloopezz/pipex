/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-s <dlopez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 17:31:32 by dlopez-s          #+#    #+#             */
/*   Updated: 2023/03/22 17:43:47 by dlopez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	bonus_son(char *cmd, char *env[])
{
	pid_t	id;
	int		xtr[2];

	pipe(xtr);
	if (xtr < 0)
		exit (EXIT_FAILURE);
	id = fork();
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

void	here_doc_loop(int *end, char *line, char *lim)
{
	while (line)
	{
		close(end[0]);
		if ((ft_strncmp(line, lim, ft_strlen(lim)) == 0)
			&& ft_strlen(line) == ft_strlen(lim) + 1)
			exit(EXIT_SUCCESS);
		write(1, "pipe heredoc> ", 14);
		write(end[1], line, ft_strlen(line));
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
}

void	ft_here_doc(char *lim)
{
	pid_t	doc;
	int		end[2];
	char	*line;

	if (pipe(end) == -1)
		exit(EXIT_FAILURE);
	doc = fork();
	if (doc < 0)
		exit(EXIT_FAILURE);
	if (doc == 0)
	{
		write(1, "pipe heredoc> ", 14);
		line = get_next_line(STDIN_FILENO);
		here_doc_loop(end, line, lim);
	}
	else
	{
		close(end[1]);
		dup2(end[0], STDIN_FILENO);
		close(end[0]);
		wait(NULL);
	}
}

void	pipex(int argc, char *argv[], char *env[])
{
	int	file1;
	int	file2;
	int	i;

	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		i = 3;
		file2 = ft_open(argv[argc - 1], HERE_DOC);
		ft_here_doc(argv[2]);
	}
	else
	{
		i = 2;
		file1 = ft_open(argv[1], INFILE);
		file2 = ft_open(argv[argc - 1], OUTFILE);
		dup2(file1, STDIN_FILENO);
		close(file1);
	}
	while (i < argc - 2)
		bonus_son(argv[i++], env);
	dup2(file2, STDOUT_FILENO);
	close(file2);
	exec_cmd(argv[argc - 2], env);
}

int	main(int argc, char *argv[], char *env[])
{
	if (argc >= 5)
		pipex(argc, argv, env);
	else
		return (1);
}
