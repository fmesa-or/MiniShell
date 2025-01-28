/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 18:22:05 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/01/28 19:39:43 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**********************************************************
*Fills t_sherpa data structure info with the t_redir list.*
**********************************************************/
t_sherpa	*ms_sherpa(t_redir *redir)
{
	t_sherpa	*sherpa;

	sherpa->typein = NULL;
	sherpa->typeout = NULL;
	sherpa->filein = NULL;
	sherpa->fileout = NULL;
	sherpa->hdocflag = false;

	if (redir->type == IN || redir->type == HDOC)
	{
		sherpa->typein = redir->type;
		if (redir->type == IN)
			sherpa->filein = redir->file;
		else
		{
			sherpa->filein = NULL;
			sherpa->hdocflag = true;
		}
	}
	if (redir->type == DOUT || redir->type == NDOUT)
	{
		sherpa->typeout = redir->type;
		sherpa->fileout = redir->file;
	}
	if (redir->next)
		sherpa = ms_sherpa(redir->next);
	return (sherpa);
}

int	ms_c_redir(t_token *token, t_redir *redir, t_sherpa *sherpa, t_data *data)
{
	int	ret;

	ret = 0;
	if (!redir)
		return (0);
	//ret = error_redir(token, redir);
	token->fd[1] = ms_tin_opener(sherpa->fileout, sherpa->typeout, token, data);
	token->fd[0] = ms_tin_opener(sherpa->filein, sherpa->typein, token, data);
	//creo que este if no es necesaria
/*	if (redir->next && !ret)
	{
		if (ms_c_redir(token, redir->next, sherpa, data))
			ret = 1;
	}
*/
//tengo dudas de si esto va aquí o antes
	if (sherpa->hdocflag == true && sherpa->typein != HDOC)
		ft_fake_hdoc(token);
	return (ret);
}

int	ms_init_redir(t_token *token, t_data *data)
{
	t_redir	*redir;

	if (!token->redir)
		return (0);
	if (token->type == BUIL || token->type == CMD)
	{
		redir = token->redir;
		return (ms_c_redir(token, redir, ms_sherpa(redir), data));
	}
	return (0);
}
