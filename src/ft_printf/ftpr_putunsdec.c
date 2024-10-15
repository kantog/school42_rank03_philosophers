/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftpr_putunsdec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclaeys <bclaeys@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 11:37:25 by bclaeys           #+#    #+#             */
/*   Updated: 2024/07/30 11:08:10 by bclaeys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

size_t	ftpr_putunsdec(unsigned int d)
{
	int		count;
	char	*symbols;

	count = 0;
	symbols = "0123456789";
	if (d >= 10)
	{
		count += ftpr_putunsdec(d / 10);
		d = d % 10;
	}
	count += ftpr_putchar(symbols[d]);
	return (count);
}
