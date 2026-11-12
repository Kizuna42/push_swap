/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_mult.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 01:14:09 by kizuna            #+#    #+#             */
/*   Updated: 2025/04/16 01:14:10 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_is_a_sep(char c, char *sep)
{
	int	i;

	i = 0;
	while (sep[i])
	{
		if (sep[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	ft_usep(char *str, char *sep)
{
	int	i;

	i = 1;
	while (ft_is_a_sep(str[i], sep) == 0 && str[i])
		i++;
	return (i);
}

static int	ft_count_malloc(char *str, char *sep)
{
	int	num_sep;
	int	i;
	int	verification;

	num_sep = 0;
	verification = 1;
	i = 0;
	while (str[i])
	{
		if (verification == 0 && ft_is_a_sep(str[i], sep))
			verification = 1;
		if (verification == 1 && ft_is_a_sep(str[i], sep) == 0)
			verification = 2;
		if (verification == 2 && (ft_is_a_sep(str[i], sep)
				|| str[i + 1] == '\0'))
		{
			verification = 0;
			num_sep++;
		}
		else
			i++;
	}
	return (num_sep);
}

static void	*ft_free(char **strs, int k)
{
	int	i;

	i = 0;
	while (i < k)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
	return (NULL);
}

char	**ft_split_mult(char *str, char *charset)
{
	char	**strs;
	int		num_sep;
	int		i;
	int		j;
	int		k;

	num_sep = ft_count_malloc(str, charset);
	strs = malloc(sizeof(char *) * (num_sep + 1));
	if (strs == NULL)
		return (NULL);
	i = 0;
	k = -1;
	while (++k < num_sep)
	{
		while (ft_is_a_sep(str[i], charset) == 1 && str[i])
			i++;
		j = ft_usep(str + i, charset);
		strs[k] = malloc(sizeof(char) * (j + 1));
		if (strs[k] == NULL)
			return (ft_free(strs, k));
		ft_strlcpy(strs[k], str + i, j + 1);
		i += j + 1;
	}
	strs[k] = 0;
	return (strs);
}
