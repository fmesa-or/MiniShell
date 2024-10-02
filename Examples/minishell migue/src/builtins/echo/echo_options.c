/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_options.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 18:04:27 by jholland          #+#    #+#             */
/*   Updated: 2024/07/11 13:49:08 by jholland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	check_e_opt(char *arg, int *e_opt)
{
	int		valid;
	int		e;

	e = 0;
	if (!arg || *(arg++) != '-')
		return (0);
	valid = 1;
	while (valid && *arg)
	{
		if (*arg == 'e')
			e = 1;
		else if (*arg == 'E')
			e = 0;
		else if (*arg != 'n')
			valid = 0;
		arg++;
	}
	if (valid && e_opt)
		*e_opt = e;
	return (valid);
}

static int	check_n_opt(char *arg, int *n_opt)
{
	int		valid;
	int		n;

	n = 0;
	if (!arg || *(arg++) != '-')
		return (0);
	valid = 1;
	while (valid && *arg)
	{
		if (*arg == 'n')
			n = 1;
		else if (*arg != 'e' && *arg != 'E')
			valid = 0;
		arg++;
	}
	if (valid && n_opt)
		*n_opt = n;
	return (valid);
}

int	is_valid_option(char *arg, int *e_opt, int *n_opt)
{
	int	out;

	out = check_e_opt(arg, e_opt);
	out = check_n_opt(arg, n_opt) || out;
	return (out);
}
