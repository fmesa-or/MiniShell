/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 22:23:42 by jholland          #+#    #+#             */
/*   Updated: 2024/07/15 18:28:22 by jholland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_path(char *bin, t_all *data)
{
	char			*try_path;
	char			*path;
	char			**dirs;
	unsigned int	i;

	path = find_var(data->exported_list, "PATH");
	if (!path)
		return (NULL);
	dirs = ft_split(path, ':');
	free(path);
	i = 0;
	while (dirs && dirs[i])
	{
		try_path = ft_strjoin(ft_strjoin(dirs[i], "/", 0, 0), bin, 1, 0);
		if (!access(try_path, F_OK))
			break ;
		free(try_path);
		try_path = NULL;
		i++;
	}
	free_ptr_array(&dirs);
	return (try_path);
}
