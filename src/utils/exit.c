/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pargev <pargev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 15:21:10 by pargev            #+#    #+#             */
/*   Updated: 2026/01/28 14:20:25 by pargev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_config_and_exit(t_config *config, char **string, char *error_message)
{
	if (config)
		free_config(config);
	if (string)
		free_string_array(string);
	exit_with_error(error_message);
}

void	exit_with_error(char *error_message)
{
	ft_putstr_fd("Error", 1);
	if (error_message)
		ft_putstr_fd(error_message, 1);
	ft_putstr_fd("\n", 1);
	exit(1);
}