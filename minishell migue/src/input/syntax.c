/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 22:14:44 by jholland          #+#    #+#             */
/*   Updated: 2024/07/15 18:28:24 by jholland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	unexpected_tk_error(t_all *data, char *c)
{
	write(2, data->prog_name, ft_strlen(data->prog_name));
	write(2, ": syntax error near unexpected token `", 38);
	write(2, c, ft_strlen(c));
	write(2, "'\n", 2);
}

static void	print_detected_error(t_redir *next_redir, t_all *data)
{
	if (!next_redir)
		unexpected_tk_error(data, "|");
	else if (next_redir->type == GT)
		unexpected_tk_error(data, ">");
	else if (next_redir->type == LT)
		unexpected_tk_error(data, "<");
	else if (next_redir->type == GGT)
		unexpected_tk_error(data, ">>");
	else if (next_redir->type == LLT)
		unexpected_tk_error(data, "<<");
}

int	valid_syntax(t_token *tokens, t_all *data)
{
	t_redir	*rdr_lst;

	while (tokens)
	{
		if (tokens->type == PIPE && tokens->next && tokens->next->type == PIPE)
		{
			print_detected_error(NULL, data);
			return (0);
		}
		rdr_lst = tokens->redir;
		while (rdr_lst)
		{
			if (!rdr_lst->file)
			{
				print_detected_error(rdr_lst->next, data);
				return (0);
			}
			rdr_lst = rdr_lst->next;
		}
		tokens = tokens->next;
	}
	return (1);
}
