/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sherpa.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:48:34 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/05/22 21:15:59 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/****************************************
*Returns "argv", adding "new" at the end*
****************************************/
static char	**ms_red_argv(char **argv, char *new, t_data *data)
{
	int		i;
	char	**newarray;

	i = 0;
	if (!argv[0])
		return (NULL);//cambiar por un error
	while (argv[i])
		i++;
	newarray = (char **)smalloc(sizeof(char *) * i + 2, data);
	if (!newarray)
	{
		throw_error("ERROR: malloc failed in ms_red_argv", NULL, NULL);
		sexit (errno, data);
	}
	i = -1;
	while (argv[++i])
		newarray[i] = argv[i];
	newarray[i] = ft_strdup(new, data);
	if (!newarray[i])
	{
		sfree(newarray, data);
		return (NULL);
	}
	newarray[i + 1] = NULL;
	return (newarray);
}

/*******************************************************************
*Checks if the command is wc, cat or grep to adapt the input redir.*
*******************************************************************/
static void	ms_redin_except(t_token *token, t_sherpa *sherpa, t_data *data)
{
	if ((ft_strcmp(token->argv[0], "wc") == 0)
		|| (ft_strcmp(token->argv[0], "cat") == 0)
		|| (ft_strcmp(token->argv[0], "grep") == 0))
	{
		token->argv = ms_red_argv(token->argv, sherpa->filein, data);
	}
}

/**********************************************************
*Fills t_sherpa data structure info with the t_redir list.*
**********************************************************/
t_sherpa	*ms_sherpa(t_token *tk, t_redir *re, t_sherpa *sh, t_token *t_prev, t_data *data)
{
	if (!sh)
		return (NULL);
	if (re->type == IN || re->type == HDOC)
	{
		sh->typein = re->type;
		if (re->type == HDOC)
			sh->hdocflag = true;
		sh->filein = re->file;
	}
	if (re->type == DOUT || re->type == NDOUT)
	{
		sh->typeout = re->type;
		sh->fileout = re->file;
	}
	if (re->next)
		sh = ms_sherpa(tk, re->next, sh, t_prev, data);
	else if (sh->typein == IN && !(tk->argv[1]))
		ms_redin_except(tk, sh, data);
	return (sh);
}
