#include "minishell.h"

int	ft_exec_builtin_env(t_command *cmd, char **envp)
{
	int i;

	if (cmd->argv[1])
	{
		ft_putstr_fd("env: too many arguments\n", 2);
		ft_set_exit_status(1);
		return (1);
	}
	i = 0;
	while (envp[i])
	{
		if (ft_strchr(envp[i], '='))
			ft_putendl_fd(envp[i], 1);
		i++;
	}
	ft_set_exit_status(0);
	return (0);
}
