/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 16:19:36 by smamalig          #+#    #+#             */
/*   Updated: 2025/09/19 16:20:33 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer/lexer_internal.h"

t_token	lex_dollar(t_lexer *lexer)
{
	if (lexer_match(lexer, '('))
	{
		if (lexer_match(lexer, '('))
			return (lexer_emit(lexer, TOK_MATH_OPEN));
		return (lexer_emit(lexer, TOK_SUB_OPEN));
	}
	return (lex_word(lexer));
}
