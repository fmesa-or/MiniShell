/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escapes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 18:07:32 by jholland          #+#    #+#             */
/*   Updated: 2024/07/11 13:49:35 by jholland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	hexadec_char(char **str);
char	octal_char(char **str);

static char	normal_escape(char c)
{
	if (c == 'a')
		return ('\a');
	else if (c == 'n')
		return ('\n');
	else if (c == 't')
		return ('\t');
	else if (c == 'f')
		return ('\f');
	else if (c == 'v')
		return ('\v');
	else if (c == 'b')
		return ('\b');
	else if (c == 'e')
		return ('\e');
	else if (c == 'r')
		return ('\r');
	return (c);
}

void	fill_escaped(char **in, char **out)
{
	if (**in == 'x' && ++(*in))
		*((*out)++) = hexadec_char(in);
	else if (**in == '0' && ++(*in))
		*((*out)++) = octal_char(in);
	else if (**in == 'n' || **in == 't' || **in == 'f' || **in == 'v'
		|| **in == 'b' || **in == 'e' || **in == 'r')
		*((*out)++) = normal_escape(*(*in)++);
	else
		*((*out)++) = *((*in)++);
}
