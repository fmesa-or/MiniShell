/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_redir2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:50:44 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/05/29 20:01:11 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_c_redir(t_token *tk, t_redir *redir, t_sherpa *sh, int *fd)
{
	t_data	*data;

	data = get_pdata(NULL);
	if (!redir)
		return (0);
	data->typein = sh->typein;
	data->typeout = sh->typeout;
	tk->l_status = err_redir(sh);
	if (tk->l_status == 0)
	{
		data->file_out = ms_tin_opener(sh->fileout,
				data->typeout, tk, fd);
		data->file_in = ms_tin_opener(sh->filein,
				data->typein, tk, fd);
	}
	if (sh->hdocflag == true && sh->typein != HDOC)
		ft_fake_hdoc(tk);
	return (tk->l_status);
}

static t_sherpa	*ms_sherpa_init(t_sherpa *sherpa)
{
	sherpa = smalloc(sizeof(t_sherpa));
	if (!sherpa)
	{
		throw_error("ERROR: malloc failed in sherpa", NULL, NULL);
		sexit(errno);
	}
	sherpa->typein = NONE;
	sherpa->typeout = NONE;
	sherpa->filein = NULL;
	sherpa->fileout = NULL;
	sherpa->hdocflag = false;
	return (sherpa);
}

int	ms_init_redir(t_token *token, int *fd, t_token *token_prev)
{
	t_redir		*redir;
	t_sherpa	*sherpa;

	sherpa = NULL;
	if (!(token->redir))
		return (0);
	if (token->type == BUIL || token->type == CMD)
	{
		sherpa = ms_sherpa_init(sherpa);
		redir = token->redir;
		return (ms_c_redir(token, redir,
				ms_sherpa(token, redir, sherpa, token_prev), fd));
	}
	return (0);
}
