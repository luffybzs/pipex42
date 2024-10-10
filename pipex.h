/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarab <ayarab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 14:35:13 by ayarab            #+#    #+#             */
/*   Updated: 2024/10/07 18:29:50 by ayarab           ###   ########.fr       */
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
	char	**paths;

	int		ac;
	int		nb_cmd;
	pid_t	*pid;
}			t_data;

//------------------------------------------------------------//

int			fill_data(t_data *data, char **av, char **env, int ac);
int			ft_verif_file(char *s1, char *s2);
int			ft_exec_cmd(t_data *data, char *command, int i);
//------------------------------------------------------------//
char		**ft_search_path(t_data *data);
char		*ft_way_path(t_data *data);
char		*ft_strjoin_free(char *s1, char *s2);
char		*ft_verif_access(char **path, char **cmd);
//------------------------------------------------------------//
void		ft_free_char(char **res);
void		ft_error_verif(char *badcmd);
void		ft_error_file(char *s1);
void		ft_child_exec_first_command(t_data *data, char *command);
void		ft_child_exec_last_command(t_data *data, char *command);
void		ft_child_exec(t_data *data, char *command);

#endif