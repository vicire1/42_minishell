#include "../../include/minishell.h"

//return quoi ? char *?

//utiliser getcwd
void	cmd_pwd(t_data *data, int fd)
{
	char	*pwd;
	t_env	*tempo;

	(void)data;
	tempo = data->first_env;
	pwd = getcwd(NULL, 0);
	if (pwd)
		ft_printf_fd(fd, "%s\n", pwd);
	else
	{
		while (tempo)
		{
			if (ft_strncmp(tempo->name, "PWD=", 4) == 0)
			{
				ft_printf_fd(fd, "%s\n", tempo->value);
				break ;
			}
			tempo = tempo->next;
		}
	}
	if (pwd)
		free(pwd);
	return ;
}
