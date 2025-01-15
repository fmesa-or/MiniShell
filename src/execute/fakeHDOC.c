/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fakeHDOC.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 19:53:19 by fmesa-or          #+#    #+#             */
/*   Updated: 2024/12/17 19:58:43 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.c"

void	fake_writer(char *line, char *limiter)
{
	if (!(ft_strncmp(line, limiter, ft_strlen(limiter)) == 0))
		write(1, "> ", 2);
	if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
		exit(EXIT_SUCCESS);
}

void	ft_fake_hdoc(t_token token)
{
	char	*line;

	write(1, "> ", 2);
	while (get_next_line_pipex(&line))
		fake_writer(line, token->hdoc);
}