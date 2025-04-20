/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 21:35:00 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/04/20 18:44:58 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/***********************************************
*1st:	Set the pipe.                          *
*2nd:	Sets the child process and executes it.*
***********************************************/
/*void	child_process(t_token *token)
{
	if (pipe(token->fd) == -1)
				throw_error("ERROR: fork didn't work as expected.", token, data);

	token->pid = fork();
	if (token->pid == -1)
		throw_error("ERROR: fork didn't work as expected.", token, data);
	else if (token->pid == 0)
	{
		close(token->fd[0]);
		dup2(token->fd[1], STDOUT_FILENO);
		ft_execute(token->type, token->env);
	}
	else
	{
		close(token->fd[1]);
		dup2(token->fd[0], STDIN_FILENO);
	}
}*/

void	ms_fds(t_token *token, t_token *token_prev, t_data *data)
{
//	printf("next token type = %d\n", token[1].type);
//	printf("actual token type = %d\n", token->type);
	if (token[1].type != NONE)
	{
		if (pipe(token->fd) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		token->fd[1] = token[1].fd[1];
	}
	if (token_prev->type != NONE)
	{
		dup2(token_prev->fd[0], STDIN_FILENO);
		close(token_prev->fd[0]);
		close(token_prev->fd[1]);
	}
//	printf("token->redir: %p\n", token->redir);
	if (token->redir)
	{
		token->l_status = ms_init_redir(token, data);
		if (token->l_status == 1)//revisar, creo que o no es necesario, o no aplica así
		{
			token_prev = token;
			close(token_prev->fd[0]);
			close(token_prev->fd[1]);
			close(token->fd[0]);// lo mismo si, lo mismo no
			return ;
		}
	}
		if (token[1].type == NONE)
			dup2(token->fd[1], STDOUT_FILENO);
	
}


void ms_commander(t_token *token, t_data *data)
{
	if (token->type != CMD && token->type != BUIL)
		return;

	if (token->type == BUIL && token[1].type == NONE)
	{
		token->l_status = ms_builts(token, data);
		printf("BUIL CHECK\n");
	}
	else
	{
		token->pid = fork();
		if (token->pid == 0) //if es el hijo
		{
			if (token->type == BUIL)
			{
//				printf(FF"CHECK BUIL"RES);
				ms_builts(token, data);
				exit(0);
			}
			else
			{
				printf("CHECK CHILDS: %s REDIR: fd[0]:%d fd[1]:%d\n"RES, token->command, token->fd[0], token->fd[1]);
				ms_exe_childs(token, data);
				//ESTAN FALLANDO LOS FILES DESCRIPTORS!!!
				//CUANDO ENTRAN MAS DE 3 PIPES LOS FD SE EMPIEZAN A RALLAR
				//REVISAR TAMBIÉN QUE PASARÁ CUANDO META REDIRECCIONES
			}
		}
		else //es el padre
		{
//			wait(NULL);
			dprintf(2, "Check PADRE: %s fd[0]:%d fd[1]:%d\n", token->command, token->fd[0], token->fd[1]);
//			if (token->fd[0] != 0)
//				close(token->fd[0]);
			if (token->fd[1] != 1)
				close(token->fd[1]);
		}
	}
}
/*   V0.4
void ms_commander(t_token *token, t_data *data)
{
    if (token->type != CMD && token->type != BUIL)
        return;

    if (token->type == BUIL && token[1].type == NONE)
    {
        token->l_status = ms_builts(token, data);
        printf("BUIL CHECK\n");
    }
    else
    {
        token->pid = fork();
        dprintf(2, "Iniciando PID: %d\n", token->pid);
        if (token->pid == 0) // Proceso hijo
        {
            // Redirigir entrada y salida
            if (token->fd[0] != 0)
            {
                dup2(token->fd[0], STDIN_FILENO);
                close(token->fd[0]);
            }
            if (token->fd[1] != 1)
            {
                dup2(token->fd[1], STDOUT_FILENO);
                close(token->fd[1]);
            }

            // Cerrar descriptores innecesarios
            if (token[1].type != NONE)
                close(token[1].fd[0]);

            // Ejecutar el comando
            if (token->type == BUIL)
            {
                ms_builts(token, data);
                exit(0);
            }
            else
            {
                ms_exe_childs(token, data);
                exit(1); // Salir si falla
            }
        }
        else // Proceso padre
        {
            // Cerrar extremos de las pipes en el padre
            if (token->fd[0] != 0)
                close(token->fd[0]);
            if (token->fd[1] != 1)
                close(token->fd[1]);
        }
    }
}*/

/*    V0.3
void ms_commander(t_token *token, t_data *data)
{
	if (token->type != CMD && token->type != BUIL)
		return;

	if (token->type == BUIL && token[1].type == NONE)
	{
		token->l_status = ms_builts(token, data);
		printf("BUIL CHECK\n");
	}
	else
	{
		token->pid = fork();
		dprintf(2, "Iniciando PID: %d\n", token->pid);
		if (token->pid == 0) // Proceso hijo
		{
			// Redirigir entrada y salida
			if (token->fd[0] != 0)
			{
				dup2(token->fd[0], STDIN_FILENO);
				close(token->fd[0]);
			}
			if (token->fd[1] != 1)
			{
				dup2(token->fd[1], STDOUT_FILENO);
				close(token->fd[1]);
			}

			// Ejecutar el comando
			if (token->type == BUIL)
			{
				ms_builts(token, data);
				exit(0);
			}
			else
			{
				ms_exe_childs(token, data);
				exit(1); // Salir si falla
			}
		}
		//else // Proceso padre
	//	{
			// Cerrar extremos de las pipes en el padre
			//if (token->fd[0] != 0)
			//	close(token->fd[0]);
			//if (token->fd[1] != 1)
			//	close(token->fd[1]);
	//	}
	}
}*/
/*    V0.2
void	ms_commander(t_token *token, t_data *data)
{
	if (token->type != CMD && token->type != BUIL)
		return ;
//	printf(RD"Token.Type = %d\n"RES, token->type);
	if (token->type == BUIL && token[1].type == NONE)
	{
		token->l_status = ms_builts(token, data);
		printf(GR"BUIL CHECK\n"RES);
	}
	else
	{
		token->pid = fork();
		dprintf(2, "Iniciando PID: %d\n", token->pid);
		if (token->pid == 0) //if es el hijo
		{
			if (token->type == BUIL)
			{
//				printf(FF"CHECK BUIL"RES);
				ms_builts(token, data);
				exit(0);
			}
			else
			{
				ms_exe_childs(token, data);
				//ESTAN FALLANDO LOS FILES DESCRIPTORS!!!
				//CUANDO ENTRAN MAS DE 3 PIPES LOS FD SE EMPIEZAN A RALLAR
				//REVISAR TAMBIÉN QUE PASARÁ CUANDO META REDIRECCIONES
			}
			//añadido BORRAR
			if (token->fd[0] != 0)
				close(token->fd[0]);
			if (token->fd[1] != 1)
				close(token->fd[1]);
		}
		else //else es el padre
		{
//			printf(PR"CHECK CLOSE\n"RES);
			//if (token->fd[0] != 0)
			close(token->fd[0]);
			//if (token->fd[1] != 1)
			close(token->fd[1]);
		}
	}
}
*/
				
			/*   V0.1
					token->pid = fork();
		if (token->pid == 0) //if es el hijo
		{
			if (token->type == BUIL)
			{
//				printf(FF"CHECK BUIL"RES);
				ms_builts(token, data);
				exit(0);
			}
			else
			{
				printf("CHECK CHILDS: %s REDIR: fd[0]:%d fd[1]:%d\n"RES, token->command, token->fd[0], token->fd[1]);
				ms_exe_childs(token, data);
				//ESTAN FALLANDO LOS FILES DESCRIPTORS!!!
				//CUANDO ENTRAN MAS DE 3 PIPES LOS FD SE EMPIEZAN A RALLAR
				//REVISAR TAMBIÉN QUE PASARÁ CUANDO META REDIRECCIONES
			}
		}
		else
		{
//			printf(PR"CHECK CLOSE\n"RES);
			if (token->fd[0] != 0)
				close(token->fd[0]);
			if (token->fd[1] != 1)
				close(token->fd[1]);
		}
	}
}
*/


/*
*token_prev es el último token
*token_post es el primer token de todo el string
*/
void	ms_main_exe(t_token *token, t_data *data)
{
	t_token	*last_token;
	t_token	*first_token;

	last_token = malloc(sizeof(t_token));
	if (!last_token)
		throw_error("ERROR: malloc didn't work as expected.", NULL, data);
//	tk_init(last_token);
	last_token->type = NONE;
	first_token = token;
	while(token->type != NONE)
	{
		ms_fds(token, last_token, data);
		ms_commander(token, data);
		last_token = token;
		token++;
		write(2, "Check while!!\n", 15);
	}
	ms_post_exe(data, last_token, first_token);





	/*    V0.1
	t_token	*token_prev;
	t_token *token_post;
//	static int j = 0;

	token_post = token;
	while(token->type != NONE)
	{
//		printf("entrada bucle\n");
		ms_fds(token, &token_prev, data);
//		printf("señal procesada en ms_fds\n");
		ms_commander(token, data);
//		printf("señal procesada en ms_commander\n");
		token_prev = token;
		token++;
//		printf("fin bucle: %d\n", ++j);
	}
	ms_post_exe(data, token_prev, token_post);
	*/
}