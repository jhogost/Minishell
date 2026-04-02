/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhervieu <hhervieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 12:42:39 by hhervieu          #+#    #+#             */
/*   Updated: 2026/04/02 12:42:39 by hhervieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	how_malloc(long n)
{
	int	res;

	res = 0;
	if (n < 0)
	{
		res++;
		n = -n;
	}
	while (n >= 10)
	{
		res++;
		n /= 10;
	}
	res++;
	return (res);
}

char	*revstr(char *str)
{
	size_t	i;
	size_t	j;
	char	temp;

	if (str[0] != '-')
		i = 0;
	else
		i = 1;
	j = ft_strlen(str) - 1;
	while ((int)i < ft_strlen(str) / 2)
	{
		temp = str[i];
		str[i] = str[j];
		str[j] = temp;
		i++;
		j--;
	}
	if (ft_strlen(str) % 2 == 1 && str[0] == '-')
	{
		temp = str[i];
		str[i] = str[j];
		str[j] = temp;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		i;
	long	nb;

	nb = n;
	str = malloc(sizeof(char) * how_malloc(nb) + 1);
	if (!str)
		return (NULL);
	i = 0;
	if (nb < 0)
	{
		nb = nb * -1;
		str[i] = '-';
		i++;
	}
	while (nb >= 10)
	{
		str[i] = (nb % 10) + '0';
		nb /= 10;
		i++;
	}
	str[i] = (nb % 10) + '0';
	str[i + 1] = '\0';
	str = revstr(str);
	return (str);
}
