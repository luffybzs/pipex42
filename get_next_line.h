/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarab <ayarab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 11:41:18 by ayarab            #+#    #+#             */
/*   Updated: 2024/10/17 15:55:00 by ayarab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include "./libft/libft.h"
# include <stdarg.h>
# include <stddef.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

char	*ft_strjoin_gnl(char *s1, char *s2);
char	*ft_strdup_gnl(char *stock, char c);
void	ft_clean_buf(char *buff);
int		ft_check_gnl(char *stock, char x);
char	*get_next_line(int fd);

#endif