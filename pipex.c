/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarab <ayarab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 14:34:29 by ayarab            #+#    #+#             */
/*   Updated: 2024/10/07 18:30:12 by ayarab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_way_path(t_data *data)
{
	int		j;
	char	*res;

	j = 0;
	while (data->env[j])
	{
		if (ft_strnstr(data->env[j], "PATH=", 5) != NULL)
		{
			res = ft_strdup(data->env[j] + 5);
			if (!res)
				return (NULL);
		}
		j++;
	}
	return (res);
}

char	**ft_search_path(t_data *data)
{
	char	*res;
	char	**tab;

	res = ft_way_path(data);
	if (!res)
		return (NULL);
	tab = ft_split(res, ':');
	if (!tab)
		return (ft_free_char(tab), NULL);
	return (free(res), tab);
}
int	fill_data(t_data *data, char **av, char **env, int ac)
{
	data->av = av;
	data->env = env;
	data->ac = ac;
	data->nb_cmd = ac - 3;
	data->pid = malloc(sizeof(pid_t) * data->nb_cmd);
	if (!data->pid)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

char	*ft_verif_access(char **path, char **cmd)
{
	int		i;
	int		verif;
	char	*tmp;

	i = 0;
	verif = access(cmd[0], F_OK | X_OK);
	if (verif == 0)
		return (ft_strdup(cmd[0]));
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		if (!tmp)
			return (NULL);
		tmp = ft_strjoin_free(tmp, cmd[0]);
		if (!tmp)
			return (NULL);
		verif = access(tmp, F_OK | X_OK);
		if (verif == 0)
			return (tmp);
		i++;
		free(tmp);
	}
	return (NULL);
}

int	main(int ac, char **av, char **env)
{
	t_data	data;
	int		status;
	int		i;

	i = 0;
	if (ac < 5)
		return (0);
	if (fill_data(&data, av, env, ac) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	while (i < data.nb_cmd)
	{
		if (ft_exec_cmd(&data, av[i + 2], i) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		i++;
	}
	i = 0;
	while (i < data.nb_cmd)
	{
		waitpid(data.pid[i], &status, 0);
		i++;
	}
	free(data.pid);
	return (0);
}
