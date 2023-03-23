/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-s <dlopez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 16:19:42 by dlopez-s          #+#    #+#             */
/*   Updated: 2023/03/23 16:26:43 by dlopez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	error_found(char *str)
{
	ft_putstr_fd(str, STDERR_FILENO);
	exit (1);
}

void	free_mtx(char **mtx)
{
	int	i;

	i = 0;
	while (mtx[i])
		free(mtx[i++]);
	free(mtx);
}

int	ft_open(char *file, int check)
{
	int	fd;

	if (check == INFILE)
	{
		fd = open(file, O_RDONLY, 0644);
		if (access(file, R_OK) < 0)
			error_found("|failed to open file| ");
	}
	if (check == OUTFILE)
	{
		fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (access(file, W_OK | R_OK) < 0)
			error_found("|failed to open file| ");
	}
	if (check == HERE_DOC)
	{
		fd = open(file, O_RDWR | O_CREAT | O_APPEND, 0644);
		if (access(file, W_OK | R_OK) < 0)
			error_found("|failed to open file| ");
	}
	if (fd < 0)
		error_found("|failed to open file| ");
	return (fd);
}
