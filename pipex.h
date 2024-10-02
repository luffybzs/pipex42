/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarab <ayarab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 14:35:13 by ayarab            #+#    #+#             */
/*   Updated: 2024/10/02 17:57:22 by ayarab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "./libft/libft.h"
# include <fcntl.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_data
{
	char	**av;
	char	**env;
	char 	**paths;

	int		nb_cmd;
	int		len;
	pid_t 	*pid;
}			t_data;

//------------------------------------------------------------//

void		ft_free_char(char **res);
int			fill_data(t_data *data, char **av, char **env, int ac);
char		**ft_search_path(t_data *data);
char		*ft_way_path(t_data *data);
int			ft_strstr_bool(char *str, char *to_find);
char		*ft_strjoin_free(char *s1, char *s2);
void 		ft_error_verif(char *badcmd);
int			ft_verif_file(char *s1, char *s2);
void 		ft_error_file(char *s1);

#endif