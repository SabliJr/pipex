/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_errs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabakar- <sabakar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 08:03:46 by sabakar-          #+#    #+#             */
/*   Updated: 2024/05/03 08:27:20 by sabakar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex_bonus.h"

void    ft_file_err(char *file)
{
    ft_putstr("Error: ");
    ft_putstr(strerror(errno));
    ft_putstr(": ");
    ft_putstr(file);
    ft_putstr("\n");
    exit(EXIT_FAILURE);
}

void    ft_cmd_err(char *cmd)
{
    ft_putstr("Command not found!");
    ft_putstr(cmd);
    ft_putstr("\n");
    exit(EXIT_FAILURE);
}

void    ft_process_err(void)
{
    perror("Error: ");
    exit(EXIT_FAILURE);
}

void    ft_args_err(void)
{
    ft_putstr("Erorr: incorrect args!\n");
    exit(EXIT_SUCCESS);
}