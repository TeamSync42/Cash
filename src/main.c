/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 11:25:13 by smamalig          #+#    #+#             */
/*   Updated: 2025/07/02 15:34:12 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "arguments.h"
#include "cash.h"

int	main(int argc, char **argv, char **envp)
{
	t_cash	cash;

	arguments_init(&cash.args, argc, argv);
	ft_printf("verbose set?: %i\n", arguments_is_set(&cash.args, "verbose"));
	(void)envp;
	return (0);
}
