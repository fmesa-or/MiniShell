/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 19:33:50 by jholland          #+#    #+#             */
/*   Updated: 2024/07/15 18:28:25 by jholland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_quotes(char **ptr);

static void	add_line(char **ptr, char c)
{
	char	*newline;

	newline = NULL;
	if (c == '\"')
		newline = readline("dquote>");
	else if (c == '\'')
		newline = readline("quote>");
	else if (c == '\\')
		newline = readline("slash>");
	if (c == '\'' || c == '\"')
		*ptr = ft_strjoin(*ptr, "\n", 1, 0);
	*ptr = ft_strjoin(*ptr, newline, 1, 1);
	check_quotes(ptr);
}

static void	check_quotes(char **ptr)
{
	char	*line;
	char	quote;
	bool	esc;

	line = *ptr;
	esc = 0;
	quote = 0;
	while (line && *line)
	{
		if (!esc && quote && *line == quote)
			quote = '\0';
		else if (!esc && !quote && (*line == '\"' || *line == '\''))
			quote = *line;
		else if (!esc && !quote && *line == '\\')
			esc = 1;
		else if (esc)
			esc = 0;
		line++;
	}
	if (!quote && !esc)
		return ;
	if (quote)
		add_line(ptr, quote);
	else if (esc)
		add_line(ptr, '\\');
}

char	*user_input(t_all *data)
{
	char	*prompt;
	char	cwd[1024];
	char	*line;

	prompt = ft_strjoin(find_var(data->exported_list, "USER"), " @ ", 1, 0);
	getcwd(cwd, sizeof(cwd));
	if (data->pwd)
		free(data->pwd);
	data->pwd = ft_strdup(cwd);
	prompt = ft_strjoin(prompt, cwd, 1, 0);
	prompt = ft_strjoin(prompt, " > ", 1, 0);
	line = readline(prompt);
	check_quotes(&line);
	if (line && *line)
		add_history(line);
	free(prompt);
	return (line);
}
