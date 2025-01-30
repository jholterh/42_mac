/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_check_file_end.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholterh <jholterh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:22:05 by jholterh          #+#    #+#             */
/*   Updated: 2025/01/30 17:44:04 by jholterh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

int	check_file_end(char *str)
{
	int	file_end_len;
	int	str_len;

	file_end_len = ft_strlen(".ber");
	str_len = ft_strlen(str);
	if (str_len < file_end_len)
	{
		ft_printf("ERROR: Wrong file type as input: "
			"File name too short\n");
		return (EXIT_FAILURE);
	}
	if (ft_strncmp(str + str_len - file_end_len, ".ber", 4))
	{
		ft_printf("ERROR: Wrong file type as input: "
			"Expected '.ber' extension\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
