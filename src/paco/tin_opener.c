/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tin_opener.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 12:48:54 by fmesa-or          #+#    #+#             */
/*   Updated: 2024/10/28 13:09:21 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "minishell.h"

/*****************************************************
*Opens the file                                      *
*O_WRONLY = Opens the file in writing mode.          *
*O_CREAT  = If the file doesn't exist, it creates it.*
*O_APPEND = Adds the content if the file exists.     *
*O_TRUNC  = Truncates to zero bytes before writting. *
*O_RDONLY = Opens the file in read mode.             *
*			Deleting any previous content.           *
*****************************************************/
int	tin_opener(char *argv, int flag)
{
	int	file;

	file = 0;
	if (flag == 0)
		file = open(argv, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else if (flag == 1)
		file = open(argv, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (flag == 2)
		file = open(argv, O_RDONLY, 0777);
	if (file == -1)
		throw_error(RD"Error: OPEN function failed.\n"RES);
	return (file);
}