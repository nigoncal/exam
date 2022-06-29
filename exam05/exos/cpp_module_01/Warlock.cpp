#include "Warlock.hpp"

Warlock::Warlock(std::string const &name, std::string const &title)
{
    this->name = name;
    this->title = title;
    std::cout << this->name << ": This looks like another boring day.\n";
}

Warlock::~Warlock()
{
    std::cout << this->name << ": My job here is done!\n";
    
    std::map<std::string, ASpell *>::iterator it = this->arr.begin();
    std::map<std::string, ASpell *>::iterator ite = this->arr.end();
    while (it != ite)
    {
        delete it->second;
        ++it;
    }
    this->arr.clear();
}

std::string const &Warlock::getName() const 
{
     return (this->name);
}
std::string const &Warlock::getTitle() const 
{ 
    return (this->title);
}

void Warlock::setTitle(std::string const &title) 
{ 
    this->title = title;
}

void Warlock::introduce() const 
{
    std::cout << this->name << ": I am " << this->name << ", " << this->title << "!\n";
}

void Warlock::learnSpell(ASpell* spell)
{
	if (spell)
		arr.insert(std::pair<std::string, ASpell *>(spell->getName(), spell->clone()));
}

void Warlock::forgetSpell(std::string spellName)
{
	std::map<std::string, ASpell *>::iterator it = arr.find(spellName);
	if (it != arr.end())
		delete it->second;
	arr.erase(spellName);
}

void Warlock::launchSpell(std::string spellName, ATarget const &target)
{
	ASpell* spell = arr[spellName];
	if (spell)
		spell->launch(target);
}
