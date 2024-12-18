/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_builts_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 12:52:06 by fmesa-or          #+#    #+#             */
/*   Updated: 2024/12/18 14:42:03 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_minusall(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] >= 'A' && s[i] <= 'Z')
			s[i] = (s[i] + 32);
	}
}

void	bi_change_dir(t_token token, t_data data)
{
	ft_minusall(&token.argv[1]);
	if (!token.argv[1] || token.argv[1] == "$home" || token.argv[1] == "~")
		token.argv[1] = "home"

}

void	ft_builtin(t_token token, t_data data)
{
	//Solo funcionan en minúsculas
	if (token->argv[0] == "cd")
		bi_change_dir(token, data);
	//Solo en mayus
	//Ambos
}
