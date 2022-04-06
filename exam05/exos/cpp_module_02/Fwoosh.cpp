/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fwoosh.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigoncal <nigoncal@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 23:24:08 by ncolomer          #+#    #+#             */
/*   Updated: 2022/04/06 13:37:46 by nigoncal         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Fwoosh.hpp"

Fwoosh::Fwoosh():
	ASpell("Fwoosh", "fwooshed") {}

Fwoosh::~Fwoosh() {}

ASpell *Fwoosh::clone(void) const 
{
	return (new Fwoosh(*this));
}
