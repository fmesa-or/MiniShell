/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_execute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 12:56:33 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/01/15 19:58:25 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* PIPEX MATERIAL */

static void	throw_error_awk(int n_error, char **awks, char **flags)
{
	ft_freearray(awks);
	ft_freearray(flags);
	perror(RD"Error: FINAL_SPLIT could not be created.\n"RES);
	exit (n_error);
}

/*******************************************************************************
*Alternative versión of ft_split so it has in consideration AWKS command.      *
*1st: Splits eith the char ' so it will catch the AWKS option if needed.       *
*2nd: Splits all flags and options outside the brackets '{}'                   *
*3rd: Messures the total length of the array with the commands.                *
*4th: Saves space in memory and uses STRDUP                                    *
*		to add everything in the final array.                                  *
*******************************************************************************/
char	**awk_split(const char *argv, int i)
{
	char	**awks;
	char	**flags;
	char	**final_split;
	int		len;

	awks = ft_split(argv, '\'');
	flags = ft_split(awks[0], ' ');
	len = 0;
	while (flags[i++])
		len++;
	if (awks[1])
		len++;
	final_split = (char **)malloc(sizeof(char *) * (len + 1));
	if (!final_split)
		throw_error_awk(1, awks, flags);
	i = -1;
	while (flags[++i])
		final_split[i] = ft_strdup(flags[i]);
	if (awks[1])
		final_split[i++] = ft_strdup(awks[1]);
	final_split[i] = NULL;
	ft_freearray(awks);
	ft_freearray(flags);
	return (final_split);
}

char	*fp_loop(char *path, char *cmd, char **paths, int i)
{
	char	*route;

	route = ft_strjoin(paths[i], "/");
	path = ft_strjoin(route, cmd);
	if (access(path, F_OK) == 0)
	{
		ft_freearray(paths);
		free (route);
		return (path);
	}
	free(route);
	free (path);
	return (NULL);
}

/*******************************************************************************
*1st: Seeks the PATH enviroment.                                               *
*2nd: Then stores inside an array all the paths in the enviroment.             *
*3rd: Adds at the end of the path the '/' character for looking inside the     *
*		command.                                                               *
*4th: If the path to the command exists returns the actual path.               *
*	If not frees everything.                                                   *
*******************************************************************************/
char	*find_path(char *cmd, char **envp)
{
	int		i;
	char	**paths;
	char	*path;

	i = 0;
	path = NULL;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		path = fp_loop(path, cmd, paths, i);
		if (!(path == NULL))
			return (path);
		i++;
	}
	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
	return (0);
}

/****************************************************************************
*Takes the comand and executes it.                                          *
*                                                                           *
*1st: Splits the full argument so it separates the comand from the flags.   *
*2nd: Finds the path to the main command.                                   *
*	If the path fails it frees all command info.                            *
*3rd: Uses EXECVE to replace the actual process with the new one.           *
	int execve(const char *filename, char *const argv[], char *const envp[])*
****************************************************************************/
void	ft_execute(char *argv, char **envp)
{
	int		i;
	char	*path;
	char	**cmd;

	i = -1;
	cmd = awk_split(argv, 0);
	path = find_path(cmd[0], envp);
	if (!path)
	{
		while (cmd[++i])
			free (cmd[i]);
		free(cmd);
		throw_error(RD"Error: Command not founded.\n"RES);
	}
	if (execve(path, cmd, envp) == -1)
		throw_error(RD"Error: EXECVE failed.\n"RES);
	free(path);
	ft_freearray(cmd);
}