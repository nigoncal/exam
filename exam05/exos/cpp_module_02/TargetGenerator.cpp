#include "TargetGenerator.hpp"

TargetGenerator::TargetGenerator(){}

TargetGenerator::~TargetGenerator()
{
    std::map<std::string, ATarget *>::iterator it = this->arr_target.begin();
    std::map<std::string, ATarget *>::iterator ite = this->arr_target.end();
    while (it != ite)
    {
        delete it->second;
        ++it;
    }
    this->arr_target.clear();
}

void TargetGenerator::learnTargetType(ATarget* target_ptr)
{
    if (target_ptr)
        arr_target.insert(std::pair<std::string, ATarget *>(target_ptr->getType(), target_ptr->clone()));
}

void TargetGenerator::forgetTargetType(const std::string &targetName)
{
    std::map<std::string, ATarget *>::iterator it = arr_target.find(targetName);
	if (it != arr_target.end())
		delete it->second;
    arr_target.erase(targetName);
}

ATarget* TargetGenerator::createTarget(const std::string &targetName)
{
    std::map<std::string, ATarget *>::iterator it = arr_target.find(targetName);
    if (it != arr_target.end())
        return arr_target[targetName];
    return NULL;
}
