/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 18:22:05 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/05/27 19:21:29 by fmesa-or         ###   ########.fr       */
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
	if (sherpa->typein == IN && (!access(sherpa->filein, F_OK) && access(sherpa->filein, R_OK)))
		return (e_red_mssg(sherpa->filein));
	if ( (sherpa->typeout != NONE) && (!access(sherpa->fileout, F_OK) && access(sherpa->fileout, W_OK)))
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
	while (argv[i])
	{
		if (access(argv[i], F_OK) == -1 || access(argv[i], R_OK) == -1)
			return (1);
		i++;
	}
	return (0);
}