#include <pipex.h>

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
	return (0); //printear errorr
}

static int	find_path(char *cmd, char **env)
{
	char	**all_paths;
	char	*cmd_path;
	int		pos;
	int		i;

	i = 0;
	pos = find_path_pos(env);
	all_paths = ft_split(env[pos] + 5,  ':');
	while (env[i])
	{
		cmd_path = ft_strjoin(cmd, "/");
		cmd_path = ft_strjoin(cmd_path, cmd);
		printf("%s", cmd_path)
		//comprobar si está
		i++;
	}

}

void	exec_cmd(char *cmd, char **env)  //cmd es argv[2] y argv[3]
{
	char	**cmd_flags;
	char	*path;

	cmd_flags = ft_split(cmd, ' ');
	path = find_path(cmd_flags[0], env);

}