/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:24:05 by rmarin-j          #+#    #+#             */
/*   Updated: 2025/05/30 13:05:26 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	tk_argvtipe(t_token *tk_list, t_list *env, t_data *data)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (tk_list->argv[i])
	{
		if (is_builtin(tk_list, tk_list->argv[i]) == 1)
		{
			if (((ft_strcmp(tk_list->argv[i], "cd") == 0)
					&& (tk_list->argv[i + 1]))
				&& (ft_strcmp(tk_list->argv[i + 1], "..") == 0))
				i++;
			flag ++;
			break ;
		}
		else if (is_cmd(tk_list->argv[i], tk_list, env, data) == 1)
		{
			flag++;
			break ;
		}
		i++;
	}
	tk_list->argc = i;
	return (flag);
}

static int	tk_l_m_sub2(t_token *tk_list, int *i, t_list *env, t_data *data)
{
	if (!tk_list->argv[0] && tk_list->redir->type == 4
		&& tk_list->redir->file)
	{
		ft_fake_hdoc(tk_list);
		ft_tokenclear(tk_list);
		tk_list->l_status = 42;
		return (1);
	}
	else if (tk_argvtipe(&tk_list[(*i)], env, data) < 1
		&& tk_list->l_status != 2)
	{
		throw_error("ERROR: command not found", NULL, NULL);
		tk_list[(*i)].l_status = 127;
		tk_list->l_status = 127;
		return (1);
	}
	return (0);
}

static int	tk_list_make_sub(char **pips, int *i, t_token *tk_l)
{
	int	j;

	j = 0;
	while (pips[(*i)][j])
	{
		while (ft_isspace(pips[(*i)][j]))
			j++;
		if (pips[(*i)][j] == '<' || pips[(*i)][j] == '>')
		{
			get_redir(&tk_l[(*i)], pips[(*i)], j);
			pips[(*i)] = rd_strdel(ft_redirlast(tk_l[(*i)].redir), pips[(*i)]);
		}
		else if (pips[(*i)][j] && (pips[(*i)][j] != '<' && pips[(*i)][j] != '>'
			&& !ft_isspace(pips[(*i)][j])))
			j = get_av(&tk_l[(*i)].av_list, pips[(*i)], j, tk_l);
		if (j == -1)
			return (-1);
	}
	return (0);
}

static t_token	*tk_lister(char **pipes)
{
	t_token	*tk_list;
	int		i;

	i = 0;
	while (pipes[i])
		i++;
	tk_list = smalloc(sizeof(t_token) * (i + 1));
	if (!tk_list)
	{
		throw_error("ERROR: smalloc failed in bm_rm_quotes",
			NULL, NULL);
		sexit(errno);
	}
	return (tk_list);
}

t_token	*tk_list_make(char **pipes, t_list *env, t_data *data)
{
	int		i;
	t_token	*tk_list;

	tk_list = tk_lister(pipes);
	i = 0;
	while (pipes[i])
	{
		if (pipes[i][0] == 0)
			break ;
		tk_init(&tk_list[i]);
		if (tk_list_make_sub(pipes, &i, tk_list) == -1)
			return (NULL);
		tk_list[i].argv = listtoargv(tk_list[i].av_list);
		if (tk_l_m_sub2(tk_list, &i, env, data) == 1)
			return (tk_list);
		i++;
	}
	tk_list[i].type = NONE;
	return (tk_list);
}
