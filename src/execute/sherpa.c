/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sherpa.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:48:34 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/05/20 16:49:02 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*******************************************************************
*Checks if the command is wc, cat or grep to adapt the input redir.*
*******************************************************************/
static void	ms_redin_except(t_token *token, t_sherpa *sherpa)
{
	if ((ft_strcmp(token->argv[0], "wc") == 0)
		|| (ft_strcmp(token->argv[0], "cat") == 0)
		|| (ft_strcmp(token->argv[0], "grep") == 0))
	{
		token->argv = ms_red_argv(token->argv, sherpa->filein);
	}
}

/**********************************************************
*Fills t_sherpa data structure info with the t_redir list.*
**********************************************************/
t_sherpa	*ms_sherpa(t_token *tk, t_redir *re, t_sherpa *sh, t_token *t_prev)
{
	if (!sh)
		return (NULL);
	if (re->type == IN || re->type == HDOC)
	{
		sh->typein = re->type;
		if (re->type == IN)
			sh->filein = re->file;
		else
		{
			sh->filein = NULL;
			sh->hdocflag = true;
		}
	}
	if (re->type == DOUT || re->type == NDOUT)
	{
		sh->typeout = re->type;
		sh->fileout = re->file;
	}
	if (re->next)
		sh = ms_sherpa(tk, re->next, sh, t_prev);
	else if (sh->typein == IN && !(tk->argv[1]))
		ms_redin_except(tk, sh);
	return (sh);
}
