/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 11:25:13 by smamalig          #+#    #+#             */
/*   Updated: 2025/07/09 18:49:41 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>

#include "arguments.h"
#include "lexer.h"
#include "parser.h"
#include "cash.h"

static void	repl(t_cash *cash)
{
	char *line;

	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		parser_parse(&cash->parser, line);
		free(line);
	}
}

int	main(int argc, char **argv, char **envp)
{
	auto t_cash cash;
	if (arguments_init(&cash.args, argc, argv))
		return (arguments_destroy(&cash.args), 2);
	lexer_init(&cash.lexer);
	ft_printf("verbose set?: %i\n", arguments_is_set(&cash.args, "verbose"));
	if (arguments_is_set(&cash.args, "posix"))
		ft_printf("Posix mode enabled\n");
	arguments_destroy(&cash.args);
	lexer_init(&cash.lexer);
	parser_init(&cash.parser, &cash.lexer);
	repl(&cash);
	(void)envp;
	return (0);
}
