/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   amp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 16:34:10 by smamalig          #+#    #+#             */
/*   Updated: 2025/09/19 16:35:42 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer/lexer_internal.h"

t_token	lex_amp(t_lexer *lexer)
{
	if (lexer_match(lexer, '&'))
	{
		if (lexer_match(lexer, ';'))
			return (lexer_emit(lexer, TOK_DOUBLE_SEMI_AMP));
		return (lexer_emit(lexer, TOK_AND));
	}
	if (lexer_match(lexer, ';'))
		return (lexer_emit(lexer, TOK_SEMI_AMP));
	return (lexer_emit(lexer, TOK_BACKGROUND));
}
