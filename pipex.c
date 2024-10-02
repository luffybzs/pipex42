/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarab <ayarab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 14:34:29 by ayarab            #+#    #+#             */
/*   Updated: 2024/10/02 19:29:24 by ayarab           ###   ########.fr       */
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
int  fill_data(t_data *data, char **av, char **env, int ac)
{
	data->av = av;
	data->env = env;
	data->nb_cmd = ac - 3;
	data->pid = malloc(sizeof(pid_t) * data->nb_cmd);
	if(!data->pid)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

char *ft_verif_access(char **path, char **cmd)
{
	int i;
	int verif;
	char *tmp;

	i = 0;
	verif = access(cmd[0], F_OK | X_OK);
	if (verif == 0)
		return (ft_strdup(cmd[0]));
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		if (!tmp)
			return(NULL);
		tmp = ft_strjoin_free(tmp, cmd[0]);
		if (!tmp)
			return(NULL);
		verif = access(tmp, F_OK | X_OK);
		if (verif == 0)
			return (tmp);
		i++;
		free(tmp);
	}
	return (NULL);
}

int 	ft_exec_cmd(t_data *data, char *command, int i)
{
	char **path;
	char **cmd;
	char *goodpath;
	// gestion des pipe
	data->pid[i] = fork();
	if (data->pid[i] == -1)
		return (EXIT_FAILURE);
	else if (data->pid[i] == 0)
	{
		cmd = ft_split(command, ' ');
		path = ft_search_path(data);
		goodpath = ft_verif_access(path,cmd);
		if (goodpath == NULL)
			return(ft_error_verif(command), EXIT_FAILURE);
		execve(goodpath, cmd,  data->env);
	}
	return (EXIT_SUCCESS);
}
int ft_verif_file(char *s1, char *s2)
{
	int fd_infil;
	int fd_outfil;

	fd_infil = open(s1, O_RDONLY);
	if (fd_infil == -1)
		return(ft_error_file(s1),EXIT_FAILURE);
	fd_outfil = open(s2, O_RDWR | O_CREAT);
	// if (fd_outfil != -1)
	// 	return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
int ft_redir(char *s1, char *s2)
{
	int verif_in;
	int verif_out;
	
	verif_in = -1;
	verif_out = -1;
	if (dup2(STDIN_FILENO , verif_in) == -1)
		return (EXIT_FAILURE);
	if (dup2(STDOUT_FILENO, verif_out) == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	main(int ac, char **av, char **env)
{
	t_data data;
	int status;
	int i;

	i = 0;
	if (ac == 0)
		return (0);
	if (fill_data(&data,av, env, ac) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (ft_verif_file(av[1], av[ac - 1]) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (ft_redir(av[1], av[ac - 1]))
		return (EXIT_FAILURE);
	while (i < data.nb_cmd)
	{
		if (ft_exec_cmd(&data, av[i + 2], i) == EXIT_FAILURE)
			return	(EXIT_FAILURE);
		i++;
	}
	i = 0;
	while (i < data.nb_cmd)
	{
		waitpid(data.pid[0], &status, 0);
		i++;
	}
	return (0);
}
