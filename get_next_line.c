/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarab <ayarab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 16:26:41 by ayarab            #+#    #+#             */
/*   Updated: 2024/10/17 15:03:00 by ayarab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	copy_after_newline(char *all, char *buff);
char	*before_newline(char *all);
char	ft_get_line(char *line, char *buff, int lu, int fd);

char	*get_next_line(int fd)
{
	char		*line;
	static char	buff[BUFFER_SIZE + 1];
	int			lu;

	lu = 1;
	if (fd > 1024 || fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	line = ft_strdup(buff);
	if (!line)
		return (NULL);
	while (lu > 0 && ft_check_gnl(line, '\n') == 0)
	{
		lu = read(fd, buff, BUFFER_SIZE);
		if (lu < 0)
			return (ft_clean_buf(buff), free(line), NULL);
		if (lu == 0)
			break ;
		free((buff[lu] = '\0', line = ft_strjoin_gnl(line, buff), NULL));
		if (!line)
			return (NULL);
	}
	ft_bzero(buff, BUFFER_SIZE + 1);
	if (!line || line[0] == '\0')
		return (ft_clean_buf(buff), free(line), NULL);
	return (copy_after_newline(line, buff), before_newline(line));
}

void	copy_after_newline(char *all, char *buff)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (all[i] != '\0' && all[i] != '\n')
		i++;
	if (all[i] == '\n')
		i++;
	while (all[i])
	{
		buff[j] = all[i];
		j++;
		i++;
	}
}

char	*before_newline(char *all)
{
	int		i;
	char	*line;

	i = 0;
	while (all[i] != '\0' && all[i] != '\n')
		i++;
	if (all[i] == '\n')
		i++;
	line = malloc(sizeof(char) * (i + 1));
	if (!line)
		return (free(all), NULL);
	i = 0;
	while (all[i] && all[i] != '\n')
	{
		line[i] = all[i];
		i++;
	}
	if (all[i] == '\n')
	{
		line[i++] = '\n';
	}
	line[i] = '\0';
	free(all);
	return (line);
}
