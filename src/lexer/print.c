/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 16:11:59 by smamalig          #+#    #+#             */
/*   Updated: 2025/09/19 16:34:03 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer/lexer_internal.h"
#include "io/ft_printf.h"

#define KEY0 "\x1b[94m"
#define KEY1 "\x1b[96m"
#define TEXT "\x1b[93m"
#define VALUE "\x1b[93m"
#define CLEAR "\x1b[m"
#define ITALIC "\x1b[3m"
#define GREY "\x1b[37m"

static const char *get_data(t_token t)
{
	return ((const char *[]){"error", "word", "var", "asgn", "<", ">", ">>",
		"<<", "<<??", "<<<", "<&", ">&", "<(", ">(", "|", "&&", "||", ";", "&",
		"\\n", "$(", "(", ")", "$((", "))", "[", "]", "[[", "]]", ";;", ";&", ";;&", "if",
		"then", "else", "fi", "while", "do", "done", "for", "in", "case",
		"esac", "select", "time", "function", "coproc", "until", "elif",
		"comment", "EOF"}[t.type]);
}

void	print_token(t_token token)
{
	ft_printf(ITALIC GREY"Token"CLEAR" ");
	ft_printf("<"TEXT"%s"CLEAR"> ", get_data(token));
	ft_printf("{"KEY0" type"CLEAR": ");
	ft_printf(VALUE"%i"CLEAR","KEY0" pos"CLEAR": {"KEY1" line"CLEAR": ",
		token.type);
	ft_printf(VALUE"%i"CLEAR","KEY1" start"CLEAR": ", token.pos.line);
	ft_printf(VALUE"%i"CLEAR","KEY1" end"CLEAR": ", token.pos.start);
	ft_printf(VALUE"%i"CLEAR","KEY1" absStart"CLEAR": ", token.pos.end);
	ft_printf(VALUE"%i"CLEAR","KEY1" absEnd"CLEAR": ", token.pos.abs_start);
	ft_printf(VALUE"%i"CLEAR" }\n", token.pos.abs_end);
}
