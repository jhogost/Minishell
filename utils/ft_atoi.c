/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhervieu <hhervieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 12:39:34 by hhervieu          #+#    #+#             */
/*   Updated: 2026/04/02 12:39:34 by hhervieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	atoi_ext(int neg, int res, int signs)
{
	if (neg % 2 == 1)
		res = -res;
	if (signs > 1)
		return (0);
	return (res);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	res;
	int	neg;
	int	signs;

	i = 0;
	neg = 0;
	res = 0;
	while ((nptr[i] >= '\t' && nptr[i] <= '\r') || nptr[i] == ' ')
		i++;
	signs = 0;
	while (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			neg++;
		signs++;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		res = res * 10 + (nptr[i] - '0');
		i++;
	}
	return (atoi_ext(neg, res, signs));
}
