/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 11:25:13 by smamalig          #+#    #+#             */
/*   Updated: 2025/07/02 13:03:03 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "cash.h"

static void parse()
{
	printf("wow\n");
}

int	main(int argc, char **argv, char **envp)
{
	t_cash	cash;
	char	*line;
	size_t	len;

	(void)cash;
	(void)argc;
	(void)argv;
	(void)envp;
	while (1)
	{
		write(1, "> ", 2);
		int out = getline(&line, &len, stdin);
		if (out == -1)
			break;
	}
	parse();
	return (0);
}
