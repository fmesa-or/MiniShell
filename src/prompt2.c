/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 16:27:25 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/05/21 23:50:10 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/********************************************************
*Adds the path from enviroment. If missing, uses getcwd.*
********************************************************/
char	*p_pwd_sub1(t_list *aux)
{
	char	*char_aux;
	char	*char_aux2;

	if (aux)
	{
		char_aux2 = ft_strdup(aux->value);
		char_aux = ft_strdup(char_aux2);
		sfree(char_aux2);
	}
	else
		char_aux = getcwd(NULL, 0);
	return (char_aux);
}

char	*p_pwd_sub2(char *old_prompt, char *char_aux, int i, int start)
{
	char	*char_aux2;
	char	*new_prompt;

	new_prompt = ft_strjoin(old_prompt, "~");
	sfree(old_prompt);
	if ((i - start) > 0)
	{
		old_prompt = ft_substr(char_aux, start, (i - start));
		char_aux2 = ft_strjoin(new_prompt, "/");
		sfree(new_prompt);
		new_prompt = ft_strjoin(char_aux2, old_prompt);
		sfree(old_prompt);
		sfree(char_aux2);
	}
	return (new_prompt);
}

char	*prompt_comp_first(char *char_aux, char *char_aux2, int i, int start)
{
	while (ft_isalpha(char_aux2[i]) != 0)
		i++;
	start = i + 1;
	while (char_aux2[i] != '.')
		i++;
	char_aux = ft_substr(char_aux2, start, (i - start));
	sfree(char_aux2);
	return (char_aux);
}
