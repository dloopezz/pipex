/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-s <dlopez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 12:57:17 by dlopez-s          #+#    #+#             */
/*   Updated: 2023/03/22 16:38:37 by dlopez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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
	exit (1);
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
	return (0);
}

void	exec_cmd(char *cmd, char **env)
{
	char	**cmd_flags;
	char	*path;

	cmd_flags = ft_split(cmd, ' ');
	path = find_path(cmd_flags[0], env);
	if (!path)
	{
		ft_putstr_fd("command not found", 2);
		exit (127);
	}
	if (execve(path, cmd_flags, env) == -1)
		exit (1);
}
