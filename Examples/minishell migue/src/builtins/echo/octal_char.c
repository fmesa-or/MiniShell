/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   octal_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 17:14:48 by jholland          #+#    #+#             */
/*   Updated: 2024/07/11 13:50:19 by jholland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isoctal(char c)
{
	return ((c >= '0' && c <= '7'));
}

char	octal_char(char **str)
{
	unsigned int	i;
	char			result;

	i = 0;
	result = 0;
	while (**str && i < 3)
	{
		if (**str >= '0' && **str <= '7')
			result = 8 * result + **str - '0';
		else
			return (result);
		(*str)++;
		i++;
	}
	return (result);
}
