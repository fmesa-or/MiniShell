/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 19:33:29 by jholland          #+#    #+#             */
/*   Updated: 2024/07/11 14:05:07 by jholland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <unistd.h>
# include <stdlib.h>

int				ft_atoi(const char *str);
void			*ft_calloc(unsigned int count, unsigned int size);
int				ft_isalpha(int c);
char			*ft_itoa(int n);
char			**ft_split(char	*str, char sep);
char			*ft_strdup(const char *s1);
char			*ft_strjoin(char *s1, char *s2, int free1, int free2);
unsigned int	ft_strlen(const char *str);
char			*ft_substr(char *str, unsigned int start, unsigned int len);

#endif