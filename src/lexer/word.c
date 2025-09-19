/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 16:06:10 by smamalig          #+#    #+#             */
/*   Updated: 2025/09/19 16:09:44 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer/lexer_internal.h"

t_token	lex_word(t_lexer *lexer)
{
	while (true)
	{
		if (lexer->next_char == '\\')
		{
			lexer_next(lexer);
			lexer_next(lexer);
		}
		if (!is_word_char(lexer->next_char))
			break ;
		lexer_next(lexer);
	}
	return (lexer_emit(lexer, TOK_WORD));
}
