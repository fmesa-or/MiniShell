/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 21:35:00 by fmesa-or          #+#    #+#             */
/*   Updated: 2024/12/16 19:34:19 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.c"

/*
*This structure only should be called on commander
*Stores the final redir and all its info
**/
typedef struct s_sherpa
{
	int		typein;
	int		typeout;
	char	*filein;
	char	*fileout;
	bool	hdocflag;
}	t_sherpa;

/**********************************************************
*Fills t_sherpa data structure info with the t_redir list.*
**********************************************************/
t_sherpa	ft_sherpa(s_redir *redir);
{
	t_sherpa	sherpa;

	while(redir->next)
	{
		if (redir->type == IN || redir->type == HDOC)
		{
			sherpa->typein = redir->type;
			sherpa->filein = redir->file;
		}
		if (redir->type == HDOC)
			sherpa->hdocflag = true;
		if (redir->type == DOUT || redir->type == NDOUT)
		{
			sherpa->typeout = redir->type;
			sherpa->fileout = redir->file;
		}
		redir = redir->next;
	}
	return(sherpa);
}

void	ft_commander(t_token *token, t_data *data)
{
	//esto es parecido al piex
	//pid está en data
	
	//token->redir -> type = IN || file = "input.txt" || next= NULL
	//token->argv -> [0]= ls; [1]=-l; [2]=-a; [3]=NULL

	//ultimo input y ultimo output

	int			filein;
	int			fileout;
	t_sherpa	sherpa;

	sherpa = ft_sherpa(token->redir);

	if (sherpa->hdocflag == true)
	{
		//hace sus cositas con el get_next_line para mostrar en pantalla
		if (sherpa->typein == HDOC)
			//hacemos el HDOC
		else
			//lo mismo que en IN

		//Esto se debe a que bash muestra en pantalla la opción de
		//escribir en el terminar dando igual cual sea la última redirección,
		//siempre que aparezca "<<", pero ejecutará como input solo la última.
	}
	else
	{
		fileout = tin_opener(sherpa->fileout, 1);
		filein = tin_opener(sherpa->filein, 2);
		dup2(filein, STDIN_FILENO);
	}

	//Probablemente aquí necesitemos una forma de llamar a ejecutar lo que
	//viene a continuación, ya que excev cierra una vez termina de ejecutar.
	//En el pipex se llama al proceso hijo, pero tengo que ver como
	//integrar esto aquí.
	/*
	El ejemplo de lo que podemos necesitar sería algo así:
	
	while ("una forma de controlar si hay otro comando a continuación")
		child_process_bonus(primer cmd y el resto en una iteración, envp);
	*/

	dup2(fileout, STDOUT_FILENO);
	ft_execute(token->type/*tenemos qu eejecutar el último comando aquí*/, token->env);
	wait(NULL);
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

void	ft_execution(t_token token, t_data data)
{

	if (token->command == "exit")
		ft_exit(token->argv);
	if (token->type == BUIL)
		ft_builtin(token->command);
	if (token->type == CMD)
		ft_commander(token, data);

	//1-Existe un comando después? -> Hacer una pipe. Modificando el fd.
	

	//2-Redirecciones ->



	//3-Hacemos fork si existe un comando despues



	//4-Hacer dup2 de los fd y close.



	//5-Comprobar tipo de comando


	/****Aquí cambia para los built in****/
	//6-Ejecutar
	//7-Del 1 al 7 en el siguiente.

}