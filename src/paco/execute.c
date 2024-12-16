/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 21:35:00 by fmesa-or          #+#    #+#             */
/*   Updated: 2024/12/16 14:40:41 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.c"

void	ft_comander(t_token *token, t_data *data)
{
	//esto es el piex
	//pid está en data
	//token->redir -> type = IN || file = "input.txt" || next= NULL
	//token->argv -> [0]= ls; [1]=-l; [2]=-a; [3]=NULL

	//ultimo input y ultimo output



	if (token->type == HDOC)
	{
		
	}
	else
	{
		filout = tin_opener();
		filein = tin_opener();
		dup2(filein, STDIN_FILENO);
	}


/*
	int	i;
	int	fileout;
	int	filein;

	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		i = 3;
		fileout = tin_opener(argv[argc - 1], 0);
		here_doc(argv[2], argc);
	}
	else
	{
		i = 2;
		fileout = tin_opener(argv[argc - 1], 1);
		filein = tin_opener(argv[1], 2);
		dup2(filein, STDIN_FILENO);
	}
	while (i < (argc - 2))
		child_process_bonus(argv[i++], envp);
	dup2(fileout, STDOUT_FILENO);
	ft_execute(argv[argc - 2], envp);
	wait(NULL);
*/



}

void	ft_builtin(char *command)
{
	if export
	if unset
	if cd
	if pwd
	if env
	if echo
}

void	ft_execute(t_token token, t_data data)
{

	if (token->command == "exit")
		ft_exit(token->argv);
	if (token->type == BUIL)
		ft_builtin(token->command);
	if (token->type == CMD)
		ft_comander(token, data);

	//1-Existe un comando después? -> Hacer una pipe. Modificando el fd.
	

	//2-Redirecciones ->



	//3-Hacemos fork si existe un comando despues



	//4-Hacer dup2 de los fd y close.



	//5-Comprobar tipo de comando


	/****Aquí cambia para los built in****/
	//6-Ejecutar
	//7-Del 1 al 7 en el siguiente.

}