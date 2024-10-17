/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarab <ayarab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 14:34:29 by ayarab            #+#    #+#             */
/*   Updated: 2024/10/17 15:54:28 by ayarab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_pipex(t_data *data)
{
	int	i;

	i = 0;
	if (data->doc == 0)
	{
		while (i < data->nb_cmd)
		{
			if (ft_exec_cmd(data, data->av[i + 2], i) == EXIT_FAILURE)
				return (EXIT_FAILURE);
			i++;
		}
	}
	else
	{
		ft_get_heredoc(data);
		while (i < data->nb_cmd)
		{
			if (ft_exec_cmd(data, data->av[i + 3], i) == EXIT_FAILURE)
				return (EXIT_FAILURE);
			if (i == 0 && data->doc == 1)
				free(data->heredoc);
			i++;
		}
	}
	return (EXIT_SUCCESS);
}

int	main(int ac, char **av, char **env)
{
	t_data	data;
	int		i;

	i = 0;
	if (ac < 5)
		return (0);
	if (fill_data(&data, av, env, ac) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (ft_pipex(&data) == EXIT_FAILURE)
		return (0);
	ft_wait_pid(&data);
	return (0);
}
