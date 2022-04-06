/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ASpell.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigoncal <nigoncal@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 23:05:57 by ncolomer          #+#    #+#             */
/*   Updated: 2022/04/06 13:44:29 by nigoncal         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ASpell.hpp"

ASpell::ASpell():
	name(), effects() {}

ASpell::ASpell(std::string const &name, std::string const &effects): name(name), effects(effects) {}

ASpell::ASpell(ASpell const &other):name(other.name), effects(other.effects) {}

ASpell::~ASpell() {}

ASpell &ASpell::operator=(ASpell const &other) 
{
	this->name = other.name;
	this->effects = other.effects;
	return (*this);
}

std::string const &ASpell::getName(void) const 
{
	return (this->name);
}

std::string const &ASpell::getEffects(void) const 
{
	return (this->effects);
}

void ASpell::launch(ATarget const &target) const 
{
	target.getHitBySpell(*this);
}
