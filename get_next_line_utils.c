/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarab <ayarab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 16:27:49 by ayarab            #+#    #+#             */
/*   Updated: 2024/10/17 15:34:58 by ayarab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_check_gnl(char *stock, char x)
{
	while (*stock)
	{
		if (*stock == x)
			return (1);
		stock++;
	}
	return (0);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = 0;
	res = malloc((sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1)));
	if (!res)
		return (free(s1), NULL);
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		res[i] = s2[j];
		j++;
		i++;
	}
	res[i] = '\0';
	return (free(s1), res);
}

char	*ft_strdup_gnl(char *stock, char c)
{
	int		i;
	char	*line;

	i = 0;
	while (stock[i] != c && stock[i])
		i++;
	line = malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (stock[i] != c && stock[i])
	{
		line[i] = stock[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

void	ft_clean_buf(char *buff)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (buff[i])
	{
		if (buff[i] == '\n')
		{
			i++;
			break ;
		}
		i++;
	}
	while (buff[i])
	{
		buff[j] = buff[i];
		j++;
		i++;
	}
	buff[j] = '\0';
}
