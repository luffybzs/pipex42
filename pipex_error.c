/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarab <ayarab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 13:43:00 by ayarab            #+#    #+#             */
/*   Updated: 2024/10/17 15:54:39 by ayarab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_error_verif(char *badcmd)
{
	ft_putstr_fd(badcmd, 2);
	ft_putstr_fd(": command not found\n", 2);
}

void	ft_error_file(char *s1)
{
	ft_putstr_fd(s1, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
}

void	ft_error_open(t_data *data)
{
	ft_putstr_fd(data->av[data->ac - 1], 2);
	ft_putstr_fd(": Permission denied\n", 2);
}
