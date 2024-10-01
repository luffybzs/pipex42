/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarab <ayarab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 14:34:29 by ayarab            #+#    #+#             */
/*   Updated: 2024/10/01 19:12:21 by ayarab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// access()

// execve();

// // tester si une fonction existe ou pas avec acces et lexecuter avec execve

// int	main(int ac, char **av, char **env)
// {
// 	acccess(av[1], env) ==
// }

int	ft_strstr_bool(char *str, char *to_find)
{
	int	i;
	int	j;

	i = 0;
	while (str[i] != '\0')
	{
		j = 0;
		while (to_find[j] == str[i + j])
		{
			if (to_find[j + 1] == '\0')
			{
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

char	*ft_way_path(t_data *data)
{
	int		len;
	int		j;
	char	*res;

	j = 0;
	while (data->env[j])
	{
		if (ft_strstr_bool(data->env[j], "/bin:") == 1)
		{
			res = ft_strdup(data->env[j]);
			if (!res)
				return (NULL);
			len = ft_strlen(res);
			res = ft_substr(res, 5, len);
			if (!res)
				return (free(res) ,NULL);
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
void fill_data(t_data *data, char **av, char **env)
{
	data->av = av;
	data->env = env;
}
int ft_verif_access(char **path, t_data *data)
{
	int i;
	int verif;
	char *tmp;

	i = 0;
	while (path[i])
	{
		tmp = ft_strjoin_free(path[i], "/");
		if (!tmp)
			return(0);
		tmp = ft_strjoin_free(tmp, data->av[1]);
		if (!tmp)
			return(0);
		verif = access(tmp, F_OK);
		printf("%d\n", verif);
		if (verif == 0)
			return (i);
		i++;
	}
	return (-1);
}
int	main(int ac, char **av, char **env)
{
	char **path;
	int goodbin;
	t_data data;
	if (ac == 5)
		return (0);
	fill_data(&data,av, env);
	path = ft_search_path(&data);
	goodbin = ft_verif_access(path,&data);
	// if (goodbin != -1)
	// {
	// 	execve(path, av[1], path[goodbin]);
	// }
	ft_free_char(path);
	return (0);
}



	// i = 0;
	// while (path[i])
	// {
	// printf("%s\n", path[i]);
	// i++;
	// }