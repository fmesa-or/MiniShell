/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 14:38:10 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/05/13 11:29:55 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*********************
*Returns $USER value.*
*********************/
static char	*prompt_user(t_list *aux, char *prompt)
{
	char	*aux_prompt;

	if (aux != NULL)
	{
		aux_prompt = ft_strdup(aux->value);
		prompt = ft_strjoin(aux_prompt, "\033[0;92m@\033[0;96m");//añade al prompt el valor(char *) de USER
		free(aux_prompt);
	}
	else
	{
		aux_prompt = ft_strdup("try_harder");
		prompt = ft_strjoin(aux_prompt, "\033[0;92m@\033[0;96m");//si USER no existe, es porque te has pasado de listillo
		free(aux_prompt);
	}
	return (prompt);
}

/***************************************************
*Adds your computer to the prompt.                 *
*(Only for 42 Campus).                             *
*1:	Adds SESSION_MANAGER value.                    *
*2:	Finds where cluster starts (cxrxsx).           *
*3:	Finds where ends, round may have 1 or 2 digits.*
*4:	Keeps what we need (cxrxxsx)                   *
*5:	Adds the computer to the prompt.               *
***************************************************/
static char	*prompt_comp(t_list *aux, char *old_prompt,char *char_aux, char *char_aux2, int i, int start)
{
	char	*new_prompt;

	if (aux != NULL)
	{
		char_aux = ft_strdup(aux->value);
		char_aux2 = ft_strdup(char_aux);
		free (char_aux);
		while (ft_isalpha(char_aux2[i]) != 0)
			i++;
		start = i + 1;
		while (char_aux2[i] != '.')
			i++;
		char_aux = ft_substr(char_aux2, start, (i - start));
		free(char_aux2);
	}
	else
	{
		char_aux = (char *)malloc(sizeof(char) * 9);
		char_aux = "harder!!";
	}
	char_aux2 = ft_strjoin(char_aux, "\033[0;92m:\033[0;96m");
	new_prompt = ft_strjoin(old_prompt, char_aux2);
	ms_free_3(old_prompt, char_aux2, char_aux);
	return (new_prompt);
}

/************************
*Adds PWD to the prompt.*
************************/
static char	*prompt_pwd(t_list *aux, char *old_prompt)
{
	char	*new_prompt;
	char	*char_aux;
	int		i;
	int		start;

	i = 0;
	start = 0;
	char_aux = p_pwd_sub1(aux);
	while (char_aux[start] && i < 1)
	{
		if (char_aux[start] == '/')
			i++;
		start++;
	}
	start--;
	i = start;
	while (char_aux[i])
		i++;
	start++;
	new_prompt = p_pwd_sub2(old_prompt, char_aux, i, start);
	old_prompt = ft_strjoin(new_prompt, "\033[0;92m$\033[0m ");
	free(new_prompt);
	new_prompt = ft_strjoin("\033[0;96m", old_prompt);
	free(old_prompt);
	return (new_prompt);
}

/*******************************************************
*This PROMPT is exclusive for 42MALAGA CAMPUS computers*
*******************************************************/
char	*ms_prompt(t_data *data)
{
	char	*prompt;
	int		i;
	int		start;

	i = 0;
	start = 0;
	prompt = NULL;
	prompt = prompt_user(find_key(data->exported_list, "USER"), prompt);
	prompt = prompt_comp(find_key(data->exported_list, "SESSION_MANAGER"),
			prompt, NULL, NULL, 0, 0);
	prompt = prompt_pwd(find_key(data->exported_list, "PWD"), prompt);
	return (prompt);
}
