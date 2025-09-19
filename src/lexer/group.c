/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   group.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 15:54:32 by smamalig          #+#    #+#             */
/*   Updated: 2025/09/19 15:56:06 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer/lexer_internal.h"
#include "lexer/token.h"

#define UNREACHABLE TOK_ERROR

t_token	lex_group(t_lexer *lexer)
{
	if (lexer->current_char == '(')
		return (lexer_emit(lexer, TOK_PAREN_OPEN));
	if (lexer->current_char == ')')
		return (lexer_emit(lexer, TOK_PAREN_CLOSE));
	return (lexer_emit(lexer, UNREACHABLE));
}
