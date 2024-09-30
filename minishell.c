/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarin-j <rmarin-j@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 16:58:21 by rmarin-j          #+#    #+#             */
/*   Updated: 2024/09/30 19:27:47 by rmarin-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **listtoenv(t_list *list)
{
    char    **env;
    int     i;

    
    i = 0;
    env = NULL;
    while (list)
    {
        //ft_strjoin + '=';
        list = list->next;
    }

}

t_list  *envtolist(char **env)
{
    t_list *list;
    int     i;
    char    **aux;

    i = 0;
    list = NULL;
    while (env[i])
    {
        aux = ft_split(env[i], "=");
        list->key = aux[0];
        list->value = aux[1];
        list = list->next;
        i++;
    }
}

int main(int argc, char **argv, char **env)
{

}
