/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-s <dlopez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 13:52:17 by dlopez-s          #+#    #+#             */
/*   Updated: 2023/03/22 16:52:31 by dlopez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include "../libft/libft.h"

# define INFILE 0
# define OUTFILE 1

void	pipex(char	*argv[], char *env[]);
void	exec_cmd(char *cmd, char **env);
int		find_path_pos(char **env);
char	*find_path(char *cmd, char **env);
void	first_son(int *xtr, char *argv[], char *env[]);
void	last_son(int *xtr, char *argv[], char *env[]);

int		error_found(char *str);
void	free_mtx(char **mtx);
int		ft_open(char *file, int check);

#endif