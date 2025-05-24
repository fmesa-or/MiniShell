/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 18:22:05 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/05/24 21:59:40 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/****************************************************
*Creates an error message and returns an error code.*
****************************************************/
int	e_red_mssg(char *file)
{
	write(2, "minishell: ", 11);
	write(2, file, ft_strlen(file));
	write(2, ": Permission denied\n", 21);
	return (1);
}

/*
*Checks the access to the filein and the fileout and the file descriptors
*/
int	err_redir(t_sherpa *sherpa)
{
	if (!access(sherpa->filein, F_OK) && access(sherpa->filein, R_OK)
		&& sherpa->typein == IN)
		return (e_red_mssg(sherpa->filein));
	if (!access(sherpa->fileout, F_OK) && access(sherpa->fileout, W_OK)
		&& (sherpa->typeout != NONE))
		return (e_red_mssg(sherpa->fileout));
	return (0);
}

/*
*Checks if arguments for command like cat or wc has access.*
*/
int	err_argv_command(char **argv)
{
	int	i;

	i = 1;
//		dprintf(2, CI"CHECK: %s\n"RES, argv[i]);
	while (argv[i])
	{
		if (access(argv[i], F_OK) == -1 || access(argv[i], R_OK) == -1)
			return (1);
		i++;
	}

/*	if (fd[0] < 0 && (sherpa->typein == IN))
		return (e_red_mssg(sherpa->filein, 1));
	if (fd[1] < 0 && (sherpa->typeout != NONE))
		return (e_red_mssg(sherpa->fileout, 1));*/
	return (0);
}