/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hexa_char.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 17:14:04 by jholland          #+#    #+#             */
/*   Updated: 2024/07/11 13:50:13 by jholland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_ishexadec(char c)
{
	return ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f')
		|| (c >= 'A' && c <= 'F'));
}

char	hexadec_char(char **str)
{
	unsigned int	i;
	char			result;

	i = 0;
	result = 0;
	while (**str && i < 2)
	{
		if (**str >= '0' && **str <= '9')
			result = 16 * result + **str - '0';
		else if (**str >= 'a' && **str <= 'f')
			result = 16 * result + **str - 'a' + 10;
		else if (**str >= 'A' && **str <= 'F')
			result = 16 * result + **str - 'A' + 10;
		else
			return (result);
		(*str)++;
		i++;
	}
	return (result);
}
