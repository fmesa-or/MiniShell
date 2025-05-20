/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 18:22:05 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/05/20 16:53:11 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/****************************************************
*Creates an error message and returns an error code.*
****************************************************/
int	e_red_mssg(char *file, int flag)
{
	if (flag == 0)
	{
		write(2, "minishell: ", 11);
		write(2, file, ft_strlen(file));
		write(2, ": Permission denied\n", 21);
		return (1);
	}
	else if (flag == 1)
	{
		write(2, "minishell: ", 11);
		write(2, file, ft_strlen(file));
		write(2, ": No such file or directory\n", 28);
		return (1);
	}
	write(2, "Internal ERROR: flag not given.\n", 32);
	return (-1);
}

/*
*Checks the access to the filein and the fileout and the file descriptors
*/
int	err_redir(t_sherpa *sherpa, int *fd)
{
	if (!access(sherpa->filein, F_OK) && access(sherpa->filein, R_OK)
		&& sherpa->typein == IN)
		return (e_red_mssg(sherpa->filein, 0));
	if (!access(sherpa->fileout, F_OK) && access(sherpa->fileout, W_OK)
		&& (sherpa->typeout != NONE))
		return (e_red_mssg(sherpa->fileout, 0));
	if (fd[0] < 0 && (sherpa->typein == IN))
		return (e_red_mssg(sherpa->filein, 1));
	if (fd[1] < 0 && (sherpa->typeout != NONE))
		return (e_red_mssg(sherpa->fileout, 1));
	return (0);
}

/****************************************
*Returns "argv", adding "new" at the end*
****************************************/
static char	**ms_red_argv(char **argv, char *new)
{
	int		i;
	char	**newarray;

	i = 0;
	if (!argv[0])
		return (NULL);//cambiar por un error
	while (argv[i])
		i++;
	newarray = (char **)malloc(sizeof(char *) * i + 2);
	if (!newarray)
	{
		throw_error("ERROR: malloc failed in ms_red_argv", NULL, NULL);
		exit (errno);
	}
	i = -1;
	while (argv[++i])
		newarray[i] = argv[i];
	newarray[i] = ft_strdup(new);
	if (!newarray[i])
	{
		free(newarray);
		return (NULL);
	}
	newarray[i + 1] = NULL;
	return (newarray);
}
