/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 21:02:33 by jholland          #+#    #+#             */
/*   Updated: 2024/07/11 14:02:49 by jholland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	get_len(int n)
{
	unsigned int	len;

	len = 0;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	if (len == 0)
		len = 1;
	return (len);
}

char	*ft_itoa(int n)
{
	char			*strnum;
	int				i;
	int				r;
	unsigned int	len;

	len = get_len(n) + (n < 0);
	strnum = malloc(len + 1);
	if (!strnum)
		return (NULL);
	if (n == 0)
		strnum[0] = '0';
	i = len - 1;
	if (n < 0)
		strnum[0] = '-';
	while (n != 0)
	{
		r = (2 * (n > 0) - 1) * (n % 10);
		n /= 10;
		strnum[i--] = r + '0';
	}
	strnum[len] = '\0';
	return (strnum);
}
