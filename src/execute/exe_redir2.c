/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_redir2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:50:44 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/05/21 21:14:59 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	ms_c_redir(t_token *tk, t_redir *redir, t_sherpa *sh, t_data *data, int *fd)
{
	int	ret;

	ret = 0;
	if (!redir)
		return (0);
	data->typein = sh->typein;
	data->typeout = sh->typeout;
	ret = err_redir(sh, fd);
	if (ret == 0)
	{
		data->file_out = ms_tin_opener(sh->fileout,
				data->typeout, tk, data, fd);
		data->file_in = ms_tin_opener(sh->filein,
				data->typein, tk, data, fd);
	}
	if (sh->hdocflag == true && sh->typein != HDOC)
		ft_fake_hdoc(tk);
	return (ret);
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

int	ms_init_redir(t_token *token, t_data *data, int *fd, t_token *token_prev)
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
				ms_sherpa(token, redir, sherpa, token_prev), data, fd));
	}
	return (0);
}

