/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fireball.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigoncal <nigoncal@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 12:49:03 by ncolomer          #+#    #+#             */
/*   Updated: 2022/04/06 13:37:53 by nigoncal         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Fireball.hpp"

Fireball::Fireball():
	ASpell("Fireball", "burnt to a crisp") {}

Fireball::~Fireball() {}

ASpell *Fireball::clone(void) const 
{
	return (new Fireball(*this));
}
