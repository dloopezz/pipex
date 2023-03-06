#include "pipex.h"

static int	find_path_pos(char **env)
{
	int i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5))
			return (i);
		i++;
	}
	return (0); //printear error
}

static char	*find_path(char *cmd, char **env)
{
	char	**all_paths;
	char	*path;
	char	*cmd_path;
	int		pos;
	int		i;

	i = 0;
	pos = find_path_pos(env);
	all_paths = ft_split(env[pos] + 5,  ':');
	while (all_paths[i])
	{
		path = ft_strjoin(all_paths[i], "/");
		cmd_path = ft_strjoin(path, cmd);
		printf("Comando: %s\n", cmd_path);
		if (access(cmd_path, X_OK) == 0)
		{
			//liberar matrix
			return (cmd_path);
		}
		i++;
	}
	exit(0); //no se ha  encontrado
}

void	exec_cmd(char *cmd, char **env)  //cmd es argv[2] y argv[3]
{
	char	**cmd_flags;
	char	*path;

	cmd_flags = ft_split(cmd, ' ');
	path = find_path(cmd_flags[0], env);
	if (execve(path, cmd_flags, env) == -1)
		exit(EXIT_FAILURE);
}