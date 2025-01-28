/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fakeHDOC.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 19:53:19 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/01/28 13:56:40 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.c"

void	fake_writer(char *line, char *limiter)
{
	if (!(ft_strncmp(line, limiter, ft_strlen(limiter)) == 0))
		write(1, "> ", 2);
	else
		return ;
}

void	ft_fake_hdoc(t_token token)
{
	char	*line;

	write(1, "> ", 2);
	while (ms_gnl(&line))
		fake_writer(line, token->hdoc);
}