/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 16:11:21 by rmarin-j          #+#    #+#             */
/*   Updated: 2025/03/26 13:17:23 by fmesa-or         ###   ########.fr       */
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
/*
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
*/

static int	export_is_key_valid(char *key)
{
	int	i;

	i = 0;
	if ((!key) || (!ft_isalpha(key[0]) && key[0] != '_'))
		return (0);
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static int	export_find_equal(char *argv)
{
	int	i;

	i = 0;
	while (argv[i] && argv[i] != '=')
		i++;
	if (!argv[i])
		return (-1);
	return (i);
}


static int	export_var(t_list *list, char *argv)
{
	int		n;
	char	*value;
	char	*key;

	value = NULL;
	//comprobar si tenenmos un igual
	n = export_find_equal(argv);
	if (n != -1)
	{
		//almacenar value & key en caso de ser correcto
		value = ft_strdup(&(argv[n + 1]));
		key = ft_substr(argv, 0, n);
	}
	//else almacenarlo todo en key
	else
		key = ft_strdup(argv);
	//comprobamos si key es valida y en caso de no serlo liberamos y mensaje de error
	if (!export_is_key_valid(key))
	{
		free(key);
		free(value);
		throw_error("ERROR: Invalid identifier\n", NULL, NULL);
		return (1);
	}
	//añadimos al ENV
	add_element_to_env(list, ft_strdup(key), ft_strdup(value));
	//liberamos
	free(key);
	free(value);
	return (0);
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
int	bi_export(t_list *list, char **argv)//(t_list, SET1="HOLA" SET2="CARACOLA")
{
	int	i;
//	int	j;
//	char	*key_aux;
//	char	*av_aux;
//	t_list	*l_aux;

i = 0;
//	j = 0;
if (!argv[1])
	export_print_declare(list);
while (argv[i])
{
	if (export_var(list, argv[i]) == 1)
		return (1);
	i++;
}
return (0);







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
}