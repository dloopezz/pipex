/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-s <dlopez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 13:52:17 by dlopez-s          #+#    #+#             */
/*   Updated: 2023/03/20 19:22:18 by dlopez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include "../libft/libft.h"

# define  DEFAULT 0  
# define  HERE_DOC 1

void	pipex(int argc, char *argv[], char *env[]);
void	exec_cmd(char *cmd, char **env);
int		find_path_pos(char **env);
char	*find_path(char *cmd, char **env);
int 	ft_infile(char **argv);
int     ft_outfile(int argc, char *argv[], int check);
void	bonus_son(char *cmd, char *env[]);
void    ft_here_doc(char *lim);


int		error_found(char *str);
void	free_mtx(char **mtx);

#endif