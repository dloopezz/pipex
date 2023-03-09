/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-s <dlopez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 12:57:17 by dlopez-s          #+#    #+#             */
/*   Updated: 2023/03/09 18:26:13 by dlopez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	error_found(char *str)
{
	ft_putstr_fd(str, STDERR_FILENO);
	exit (EXIT_FAILURE);
}

void	free_mtx(char **mtx)
{
	int	i;

	i = 0;
	while (mtx[i++])
		free(mtx[i]);
	free(mtx);
}

int	find_path_pos(char **env)
{
	int	i;

	i = 0;
	while (env[i++])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (i);
	}
	error_found("path not found");
	return (1);
}

char	*find_path(char *cmd, char **env)
{
	char	**all_dir;
	char	*slash_cmd;
	char	*path;
	int		pos;
	int		i;

	i = 0;
	pos = find_path_pos(env);
	all_dir = ft_split(env[pos] + 5, ':');
	while (all_dir[i])
	{
		slash_cmd = ft_strjoin("/", cmd);
		path = ft_strjoin(all_dir[i], slash_cmd);
		free(slash_cmd);
		if (access(path, X_OK) == 0)
		{
			free_mtx(all_dir);
			return (path);
		}
		free(path);
		i++;
	}
	free_mtx(all_dir);
	error_found("command not found");
	return (0);
}

void	exec_cmd(char *cmd, char **env) //cmd es argv[2] y argv[3]
{
	char	**cmd_flags;
	char	*path;

	cmd_flags = ft_split(cmd, ' ');
	path = find_path(cmd_flags[0], env);
	if (execve(path, cmd_flags, env) == -1)
		error_found("command not found");
}
