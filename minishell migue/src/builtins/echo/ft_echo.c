/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 13:23:06 by jholland          #+#    #+#             */
/*   Updated: 2024/07/15 18:28:21 by jholland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_valid_option(char *arg, int *e_opt, int *n_opt);
void	fill_escaped(char **in, char **out);

static char	*allocate_output(char **argv, int e_opt, int n_opt)
{
	unsigned int	len;
	char			*str;
	int				esc;

	esc = 0;
	len = 0;
	while (*argv)
	{
		str = *argv;
		while (*str)
		{
			if (esc && *str == 'x')
				hexadec_char(&str);
			else if (esc && *str == '0')
				octal_char(&str);
			else if (e_opt && !esc && *str == '\\')
				esc = 1;
			else
				len++;
			str++;
		}
		if (*(++argv))
			len++;
	}
	return (malloc(len + 1 + !n_opt));
}

static void	fill_with_arg(char *arg, char **out, int e_opt)
{
	int	esc;

	esc = 0;
	while (*arg)
	{
		if (esc)
		{
			esc = 0;
			fill_escaped(&arg, out);
		}
		else if (e_opt && !esc && *arg == '\\')
		{
			esc = 1;
			arg++;
		}
		else
			*((*out)++) = *(arg++);
	}
}

static void	fill_output(char **argv_no_opt, char *out, int e_opt, int n_opt)
{
	if (!out)
		return ;
	while (*argv_no_opt)
	{
		fill_with_arg(*argv_no_opt, &out, e_opt);
		if (*(++argv_no_opt))
			*(out)++ = ' ';
	}
	if (!n_opt)
		*(out++) = '\n';
	*out = '\0';
}

int	ft_echo(char **argv)
{
	char			*str;
	int				e_opt;
	int				n_opt;
	int				exit_code;

	exit_code = 0;
	argv++;
	e_opt = 0;
	n_opt = 0;
	while (is_valid_option(*argv, &e_opt, &n_opt))
		argv++;
	str = allocate_output(argv, e_opt, n_opt);
	fill_output(argv, str, e_opt, n_opt);
	if (write(1, str, ft_strlen(str)) == -1)
		exit_code = 1;
	free(str);
	return (exit_code);
}
