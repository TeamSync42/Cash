/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   letter_i.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 16:28:02 by smamalig          #+#    #+#             */
/*   Updated: 2025/09/19 16:28:52 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer/lexer_internal.h"

t_token	lex_letter_i(t_lexer *lexer)
{
	if (lexer_match(lexer, 'f') && !is_word_char(lexer->next_char))
		return (lexer_emit(lexer, TOK_IF));
	if (lexer_match(lexer, 'n') && !is_word_char(lexer->next_char))
		return (lexer_emit(lexer, TOK_IN));
	return (lex_word(lexer));
}
