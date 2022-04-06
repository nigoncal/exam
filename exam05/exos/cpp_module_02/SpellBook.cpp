/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SpellBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigoncal <nigoncal@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 12:54:32 by ncolomer          #+#    #+#             */
/*   Updated: 2022/04/06 13:28:16 by nigoncal         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "SpellBook.hpp"

SpellBook::SpellBook() {}

SpellBook::~SpellBook() 
{
	std::vector<ASpell*>::iterator ite = this->spells.end();
	for (std::vector<ASpell*>::iterator it = this->spells.begin(); it != ite; ++it)
		delete *it;
	this->spells.clear();
}

void SpellBook::learnSpell(ASpell *spell) 
{
	if (spell) 
	{
		std::vector<ASpell*>::iterator ite = this->spells.end();
		for (std::vector<ASpell*>::iterator it = this->spells.begin(); it != ite; ++it)
			if ((*it)->getName() == spell->getName())
				return ;
		this->spells.push_back(spell->clone());
	}
}

void SpellBook::forgetSpell(std::string const &spellName) 
{
	std::vector<ASpell*>::iterator ite = this->spells.end();
	for (std::vector<ASpell*>::iterator it = this->spells.begin(); it != ite; ++it) 
	{
		if ((*it)->getName() == spellName) 
		{
			delete *it;
			it = this->spells.erase(it);
		}
	}
}

ASpell *SpellBook::generateSpell(std::string const &spellName) 
{
	std::vector<ASpell*>::iterator ite = this->spells.end();
	for (std::vector<ASpell*>::iterator it = this->spells.begin(); it != ite; ++it) 
	{
		if ((*it)->getName() == spellName) 
			return (*it);
	}
	return (nullptr);
}
