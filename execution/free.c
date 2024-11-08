/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prizmo <prizmo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 02:55:16 by zelbassa          #+#    #+#             */
/*   Updated: 2024/11/08 17:28:26 by prizmo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void free_list(t_list *list)
{
    t_list *temp;

    while (list)
    {
        temp = list;
        list = list->next;
        free(temp->content); // Free the content of the node
        free(temp);          // Free the node itself
    }
}

// Function to free the t_cmd structure
void free_cmd(t_cmd *cmd)
{
    t_cmd *temp;

    while (cmd)
    {
        temp = cmd;
        cmd = cmd->next;

        if (temp->argv)
            free_arr(temp->argv); // Free the argv array
        if (temp->cmd)
            free(temp->cmd); // Free the cmd string
        if (temp->pipe_fd)
            free(temp->pipe_fd); // Free the pipe_fd array
        if (temp->io_fds)
        {
            if (temp->io_fds->infile)
                free(temp->io_fds->infile); // Free the infile string
            if (temp->io_fds->outfile)
                free(temp->io_fds->outfile); // Free the outfile string
            if (temp->io_fds->heredoc_name)
                free(temp->io_fds->heredoc_name); // Free the heredoc_name string
            free(temp->io_fds); // Free the io_fds structure
        }
        free(temp); // Free the t_cmd node
    }
}

// Function to free the t_data structure
int	free_data(t_data *data, int exit_code)
{
    // if (data->head)
    //     free_list(data->head); // Free the head linked list
    // if (data->arg)
    //     free(data->arg); // Free the arg string
    if (data->envp)
        free_list(data->envp); // Free the envp linked list
    if (data->cmd)
        free_cmd(data->cmd); // Free the cmd linked list
    if (data->envp_arr)
        free_arr(data->envp_arr); // Free the envp_arr array
    if (data->curr_dir)
        free(data->curr_dir); // Free the curr_dir string
    if (data->old_dir)
        free(data->old_dir); // Free the old_dir string
	return (0);
}
