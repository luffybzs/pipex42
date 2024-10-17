/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_pipex.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarab <ayarab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 22:09:48 by ayarab            #+#    #+#             */
/*   Updated: 2024/10/17 15:54:09 by ayarab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_way_path(t_data *data)
{
	int		j;
	char	*res;

	j = 0;
	if (data->env == NULL)
		return (NULL);
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

char	*ft_verif_access(char **path, char **cmd)
{
	int		i;
	int		verif;
	char	*tmp;

	i = 0;
	if (cmd[0] == NULL)
		return (NULL);
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

void	ft_get_heredoc(t_data *data)
{
	char	*line;

	data->heredoc = ft_strdup("");
	while (1)
	{
		ft_putstr_fd("heredoc> ", STDERR_FILENO);
		line = get_next_line(STDIN_FILENO);
		if (line == NULL)
			break ;
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		if (ft_strcmp(line, data->av[2]) == 0)
		{
			free(line);
			break ;
		}
		data->heredoc = ft_strjoin_free(data->heredoc, line);
		data->heredoc = ft_strjoin_free(data->heredoc, "\n");
		free(line);
	}
}
