/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delim.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 15:52:15 by smamalig          #+#    #+#             */
/*   Updated: 2025/09/19 15:53:02 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer/lexer_internal.h"
#include "lexer/token.h"

t_token	lex_delim(t_lexer *lexer)
{
	if (lexer_match(lexer, ';'))
		return (lexer_emit(lexer, TOK_DOUBLE_SEMI));
	return (lexer_emit(lexer, TOK_SEMI));
}
