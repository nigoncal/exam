/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Polymorph.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigoncal <nigoncal@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 12:49:28 by ncolomer          #+#    #+#             */
/*   Updated: 2022/04/06 13:37:27 by nigoncal         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Polymorph.hpp"

Polymorph::Polymorph():
	ASpell("Polymorph", "turned to a sheep") {}

Polymorph::~Polymorph() {}

ASpell *Polymorph::clone(void) const 
{
	return (new Polymorph(*this));
}
