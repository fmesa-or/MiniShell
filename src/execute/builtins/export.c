/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 16:11:21 by rmarin-j          #+#    #+#             */
/*   Updated: 2025/03/26 11:34:37 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/*
static void	ft_lstadd_second(t_list **lst, t_list *new)
{
	t_list *tmp;

	tmp = (*lst)->next;
	(*lst)->next = new;
	new->next = tmp;
}
*/



/*Esta funcion busca dentro de la lista donde se encuentra una key
y retorna el nodo en el que esta o null si no lo encuetra*/

t_list	*find_key(t_list *list, char *n_key)
{
	while (list != NULL)
	{
		if (ft_strcmp(list->key, n_key) == 0)
			return (list);
		list = list->next;
	}
	return (NULL);
}

/******************************************************************************
*This function prints the env to the screen with "declare -x" before each line*
******************************************************************************/
void	export_print_declare(t_list *list)
{
	while (list)
	{
		write(1, "declare -x ", 11);
		write(1, list->key, ft_strlen(list->key));
		write(1, "=\"", 2);
		if (list->value)
			write(1, list->value, ft_strlen(list->value));
		write(1, "\"\n", 2);
		list = list->next;
	}

}

/*
*This function will create and modify keys and their values according to the argument passed to it
must be called within a while loop so that the args with index are passed to it*/
int	bi_export(t_list *list, char *argv)//(t_list, VARIABLE="HOLA")
{
//	int	i;
//	int	j;
//	char	*key_aux;
//	char	*av_aux;
//	t_list	*l_aux;

//	i = 0;
//	j = 0;
	if (!argv)
		export_print_declare(list);


/*	V0.2
	while (argv[i] != '=')
		i++;
	key_aux = (char *)malloc(sizeof(char) * (i + 1));
	i = -1;
	while (argv[++i] != '=')
		key_aux[i] = argv[i];
	key_aux[i] = '\0';
	i++;
	if (argv[i] == '"' && argv[i + 1] != '"')
		i++;
	else
		printf("Lanzar ERROR y terminar\n");
	while (argv[i + j] != '"')
	{
		if (argv[i + j] == '\0')
			printf("Lanzar ERROR y terminar\n");
		j++;
	}
	av_aux = (char *)malloc(sizeof(char) * (j));
	j = -1;
	while (argv[++j + i] != '"')
		av_aux[j] = argv[i + j];
	av_aux[j] = '\0';
//	printf("n_key: %s\nav: %s\n", key_aux, av_aux);
	l_aux = (t_list *)malloc(sizeof(t_list));
	l_aux = find_key(list, key_aux);
//	printf("l_aux: %p\n", l_aux);
	if (!l_aux)
	{
		//significa que NO EXISTE previamente la variable de entorno, por lo que vamos a crear una nueva al final de la lista
		printf("CHECK ADDBACK\n");
		ft_lstadd_second(&list, ft_lstnew(key_aux, av_aux));
	}
	else
	{
		//significa que SI EXISTE previamente, por lo que vamos a sustituir el valor que se almacena en list->value
	}




	//buscar si ya existe el nodo que hemos declarado en key_aux


	if (list)
		i = 0;
*/


//	printf("key: %s\n", n_key);
	/*	V0.1
	
	char	**aux;
	t_list	*node;


	if (!n_key)
	{
		bi_voidexport(list);
		return (0);
	}
	if (n_key[0] == '=')
		return (-1);
	aux = ft_split (n_key, '=');
	node = find_key(list, aux[0]);
	if (node)
	{
		if (aux[1])
			node->value = aux[1];
	}
	else
		ft_lstadd_back(&list, ft_lstnew(aux[0], aux[1]));
		*/




//	free(key_aux);
//	free(av_aux);
	return (0);
}