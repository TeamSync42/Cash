/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 14:46:12 by smamalig          #+#    #+#             */
/*   Updated: 2025/09/19 15:43:21 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer/lexer.h"

t_result	lexer_init(t_lexer *lexer, char *input)
{
	lexer->input = input;
	lexer->end = false;
	lexer->current_char = '\0';
	lexer->next_char = input[0];
	lexer->iterator = 0;
	lexer->character = 1;
	lexer->line = 1;
	lexer->start = 0;
	lexer->abs_start = 0;
	lexer->fd = 0;
	return (RESULT_OK);
}
