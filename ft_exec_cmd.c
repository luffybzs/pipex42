/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarab <ayarab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 14:12:11 by ayarab            #+#    #+#             */
/*   Updated: 2024/10/07 18:29:23 by ayarab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_child_exec_first_command(t_data *data, char *command)
{
	char	**path;
	char	**cmd;
	char	*goodpath;
	int		fd_infil;

	fd_infil = open(data->av[1], O_RDONLY);
	if (fd_infil == -1)
		(ft_error_file(data->av[1]), exit(EXIT_FAILURE));
	if (dup2(fd_infil, STDIN_FILENO) == -1)
		exit(EXIT_FAILURE);
	cmd = ft_split(command, ' ');
	path = ft_search_path(data);
	goodpath = ft_verif_access(path, cmd);
	if (goodpath == NULL)
		(ft_error_verif(command), exit(EXIT_FAILURE));
	execve(goodpath, cmd, data->env);
	exit(EXIT_FAILURE);
}

void	ft_child_exec_last_command(t_data *data, char *command)
{
	char	**path;
	char	**cmd;
	char	*goodpath;
	int		fd_outfil;

	fd_outfil = open(data->av[data->ac - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (dup2(fd_outfil, STDOUT_FILENO) == -1)
		exit(EXIT_FAILURE);
	cmd = ft_split(command, ' ');
	path = ft_search_path(data);
	goodpath = ft_verif_access(path, cmd);
	if (goodpath == NULL)
		(ft_error_verif(command), exit(EXIT_FAILURE));
	execve(goodpath, cmd, data->env);
	exit(EXIT_FAILURE);
}

void	ft_child_exec(t_data *data, char *command)
{
	char	**path;
	char	**cmd;
	char	*goodpath;

	cmd = ft_split(command, ' ');
	path = ft_search_path(data);
	goodpath = ft_verif_access(path, cmd);
	if (goodpath == NULL)
		(ft_error_verif(command), exit(EXIT_FAILURE));
	execve(goodpath, cmd, data->env);
	exit(EXIT_FAILURE);
}

int	ft_exec_cmd(t_data *data, char *command, int i)
{
	int	fd[2];

	if (pipe(fd) == -1)
		return (EXIT_FAILURE);
	data->pid[i] = fork();
	if (data->pid[i] == -1)
		return (EXIT_FAILURE);
	else if (data->pid[i] == 0)
	{
		close(fd[0]);
		if (i < data->nb_cmd - 1)
			dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		if (i == 0)
			ft_child_exec_first_command(data, command);
		else if (i == data->nb_cmd - 1)
			ft_child_exec_last_command(data, command);
		else
			ft_child_exec(data, command);
	}
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	return (EXIT_SUCCESS);
}
