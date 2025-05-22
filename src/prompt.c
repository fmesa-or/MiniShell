/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 14:38:10 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/05/22 23:44:59 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*********************
*Returns $USER value.*
*********************/
static char	*prompt_user(t_list *aux, char *prompt, t_data *data)
{
	char	*aux_prompt;

	if (aux != NULL)
	{
		aux_prompt = ft_strdup(aux->value, data);
		prompt = ft_strjoin(aux_prompt, "\033[0;92m@\033[0;96m", data);
//		sfree(aux_prompt, data);
	}
	else
	{
		aux_prompt = ft_strdup("try_harder", data);
		prompt = ft_strjoin(aux_prompt, "\033[0;92m@\033[0;96m", data);
//		sfree(aux_prompt, data);
	}
	return (prompt);
}

/**************************************************
*Aux function for prompt_comp so norminette works.*
**************************************************/
static char	*p_c_1(char *o_prompt, char *n_prompt, char *c_aux, char *c_aux2, t_data *data)
{
	c_aux2 = ft_strjoin(c_aux, "\033[0;92m:\033[0;96m", data);
	n_prompt = ft_strjoin(o_prompt, c_aux2, data);
	return (n_prompt);
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
static char	*prompt_comp(t_list *aux, char *old_prompt, int i, int start, t_data *data)
{
	char	*new_prompt;
	char	*char_aux;
	char	*char_aux2;

	new_prompt = NULL;
	char_aux = NULL;
	char_aux2 = NULL;
	if (aux != NULL)
	{
		char_aux2 = ft_strdup(aux->value, data);
		char_aux = prompt_comp_first(char_aux, char_aux2, i, start, data);
	}
	else
	{
		char_aux = (char *)smalloc((sizeof(char) * 9), data);
//		if (!char_aux)
//			throw_error("ERROR: smalloc fatal failure.", NULL, NULL);
		char_aux = "harder!!";
	}
	new_prompt = p_c_1(old_prompt, new_prompt, char_aux, char_aux2, data);
//	sfree(old_prompt, data);
	if (ft_isalpha(char_aux[0]) == 0 || ft_isalnum(char_aux[0] == 0))
		sfree(char_aux, data);
	return (new_prompt);
}

/************************
*Adds PWD to the prompt.*
************************/
static char	*prompt_pwd(t_list *aux, char *old_prompt, t_data *data)
{
	char	*new_prompt;
	char	*char_aux;
	int		i;
	int		start;

	i = 0;
	start = 0;
	char_aux = p_pwd_sub1(aux, data);
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
	new_prompt = p_pwd_sub2(old_prompt, char_aux, i, start, data);
	old_prompt = ft_strjoin(new_prompt, "\033[0;92m$\033[0m ", data);
//	sfree(new_prompt, data);
	new_prompt = ft_strjoin("\033[0;96m", old_prompt, data);
//	sfree(old_prompt, data);
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
	prompt = prompt_user(find_key(data->exported_list, "USER"), prompt, data);
	prompt = prompt_comp(find_key(data->exported_list, "SESSION_MANAGER"),
			prompt, 0, 0, data);
	prompt = prompt_pwd(find_key(data->exported_list, "PWD"), prompt, data);
	i = ft_strlen(prompt);
	prompt[i] = '\0';
	printf("%s\n", prompt);
	return (prompt);
}
