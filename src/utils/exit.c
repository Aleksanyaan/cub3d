/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaleksan <zaleksan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 13:43:48 by zaleksan          #+#    #+#             */
/*   Updated: 2026/06/18 13:43:51 by zaleksan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_and_exit(t_config *config, char **string, char *error_msg)
{
	if (config)
		free_config(config);
	if (string)
		free_string_array(string);
	exit_with_error(error_msg);
}

void	exit_with_error(char *error_msg)
{
	ft_putstr_fd("Error", 1);
	if (error_msg)
		ft_putstr_fd(error_msg, 1);
	ft_putstr_fd("\n", 1);
	exit(1);
}
