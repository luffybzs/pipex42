/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarab <ayarab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 17:55:47 by ayarab            #+#    #+#             */
/*   Updated: 2024/10/17 15:55:27 by ayarab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free_char(char **res)
{
	int	i;

	i = 0;
	while (res[i])
	{
		free(res[i]);
		i++;
	}
	free(res);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	str = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * (sizeof(char)));
	if (!str)
		return (free(s1), NULL);
	while (s1[i])
	{
		str[j] = s1[i];
		i++;
		j++;
	}
	i = 0;
	while (s2[i])
	{
		str[j] = s2[i];
		i++;
		j++;
	}
	str[j] = '\0';
	free(s1);
	return (str);
}

void	ft_wait_pid(t_data *data)
{
	int	i;
	int	status;

	i = 0;
	while (i < data->nb_cmd)
	{
		waitpid(data->pid[i], &status, 0);
		i++;
	}
	free(data->pid);
}

int	fill_data(t_data *data, char **av, char **env, int ac)
{
	data->doc = 0;
	data->nb_cmd = ac - 3;
	if (ac >= 6 && ft_strncmp("here_doc\0", av[1], 9) == 0)
	{
		data->nb_cmd = ac - 4;
		data->doc = 1;
	}
	data->av = av;
	data->env = env;
	data->ac = ac;
	data->pid = malloc(sizeof(pid_t) * data->nb_cmd);
	if (!data->pid)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
