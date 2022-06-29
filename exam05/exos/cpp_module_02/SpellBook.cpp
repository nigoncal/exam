#include "SpellBook.hpp"

SpellBook::SpellBook() {}

SpellBook::~SpellBook()
{
    std::map<std::string, ASpell *>::iterator it = this->arr_spell.begin();
    std::map<std::string, ASpell *>::iterator ite = this->arr_spell.end();
    while (it != ite)
    {
        delete it->second;
        ++it;
    }
    this->arr_spell.clear();
}

void SpellBook::learnSpell(ASpell* spell)
{
    if (spell)
        arr_spell.insert(std::pair<std::string, ASpell *>(spell->getName(), spell->clone()));
}

void SpellBook::forgetSpell(std::string const &spellName)
{
    std::map<std::string, ASpell *>::iterator it = arr_spell.find(spellName);
	if (it != arr_spell.end())
		delete it->second;
    arr_spell.erase(spellName);
}

ASpell* SpellBook::createSpell(std::string const &spellName)
{
    std::map<std::string, ASpell *>::iterator it = arr_spell.find(spellName);
    if (it != arr_spell.end())
        return arr_spell[spellName];
    return NULL;
}
