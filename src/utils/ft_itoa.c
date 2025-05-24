/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 13:54:04 by rmarin-j          #+#    #+#             */
/*   Updated: 2025/05/21 23:36:37 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cont_dig(int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n = -n;
		i++;
	}
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*aux_ft(int dig, int n, char *s)
{
	while (dig >= 0)
	{
		s[dig] = ((n % 10) + '0');
		n /= 10;
		if ((dig == 1) && (s[0] == '-'))
			dig--;
		dig--;
	}
	return (s);
}

char	*ft_itoa(int n)
{
	char	*s;
	int		dig;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	dig = cont_dig(n);
	s = smalloc(sizeof(char) * (dig + 1));
	if (!s)
		return (NULL);
	s[dig] = '\0';
	if (n < 0)
	{
		s[0] = '-';
		n *= -1;
	}
	else
		s[0] = '0';
	dig--;
	aux_ft(dig, n, s);
	return (s);
}
