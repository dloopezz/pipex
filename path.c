#include "pipex.h"

static void free_mtx(char **mtx)
{
	int i;

	i = 0;
	while (mtx[i])
	{
		free(mtx[i]);
		i++;
	}
	free(mtx);
}

static int	find_path_pos(char **env)
{
	int i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (i);
		i++;
	}
	exit(1);
	return (0); //printear error
}


static char	*find_path(char *cmd, char **env)
{
	char	**all_paths;
	char	*path;
	char	*cmd_path;
	int		pos;
	int		i;

	pos = find_path_pos(env);
	all_paths = ft_split(env[pos] + 5,  ':');
	i = 0;
	while (all_paths[i])
	{
		path = ft_strjoin(all_paths[i], "/");
		cmd_path = ft_strjoin(path, cmd);
		free(path);
		if (access(cmd_path, F_OK) == 0)
		{
			free_mtx(all_paths);
			return (cmd_path);
		}
		i++;
	}
	free_mtx(all_paths);
	exit(0); //no se ha  encontrado
}

static void	error_found(char *str)
{
	ft_putstr_fd("ERROR:\n", 2);
	ft_putstr_fd(str, 2);
	exit (EXIT_FAILURE);
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