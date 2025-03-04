/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions_check.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholterh <jholterh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:22:25 by jholterh          #+#    #+#             */
/*   Updated: 2025/01/30 17:19:50 by jholterh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

void	free_string(char **str, int str_count)
{
	int	i;

	if (!str)
		return ;
	i = -1;
	while (++i < str_count)
		free(str[i]);
	free(str);
}
