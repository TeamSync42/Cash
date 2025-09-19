/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   letter_e.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 16:23:09 by smamalig          #+#    #+#             */
/*   Updated: 2025/09/19 16:24:43 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer/lexer_internal.h"

t_token	lex_letter_e(t_lexer *lexer)
{
	if (lexer_match(lexer, 'l'))
	{
		if (lexer_match(lexer, 's')
			&& lexer_match(lexer, 'e')
			&& !is_word_char(lexer->next_char))
		{
			return (lexer_emit(lexer, TOK_ELSE));
		}
		if (lexer_match(lexer, 'i')
			&& lexer_match(lexer, 'f')
			&& !is_word_char(lexer->next_char))
		{
			return (lexer_emit(lexer, TOK_ELIF));
		}
	}
	return (lex_word(lexer));
}
