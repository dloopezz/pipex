#include "pipex.h"

int	error_found(char *str)
{
	ft_putstr_fd(str, 2);
	exit (EXIT_FAILURE);
}

void free_mtx(char **mtx)
{
	int i;

	i = 0;
	while (mtx[i++])
		free(mtx[i]);
	free(mtx);
}

int	find_path_pos(char **env)
{
	int i;

	i = 0;
	while (env[i++])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (i);
	}
	error_found("Unable to find PATH in environment");
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
	all_dir = ft_split(env[pos] + 5,  ':');
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
	error_found("Unable to find command");
	return (0);
}

void	exec_cmd(char *cmd, char **env)  //cmd es argv[2] y argv[3]
{
	char	**cmd_flags;
	char	*path;

	cmd_flags = ft_split(cmd, ' ');
	path = find_path(cmd_flags[0], env);
	if (execve(path, cmd_flags, env) == -1)
		error_found("execve error");
}
