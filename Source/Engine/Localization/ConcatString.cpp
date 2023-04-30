#include "ConcatString.h"

using namespace cocos2d;

ConcatString* ConcatString::create(std::vector<LocalizedString*> localizedStrings)
{
	ConcatString* instance = new ConcatString(localizedStrings);

	instance->autorelease();

	return instance;
}

LocalizedString* ConcatString::clone()
{
	std::vector<LocalizedString*> clonedReplacementVariables = std::vector<LocalizedString*>();

	for (LocalizedString* next : this->getStringReplacementVariables())
	{
		clonedReplacementVariables.push_back(next == nullptr ? next : next->clone());
	}

	LocalizedString* clonedString = ConcatString::create(clonedReplacementVariables);
	
	clonedString->setOverrideLanguage(this->getOverrideLanguage());
	
	return clonedString;
}

ConcatString::ConcatString(std::vector<LocalizedString*> localizedStrings) : LocalizedString()
{
	for (int index = 0; index < int(localizedStrings.size()); index++)
	{
		this->concatString += "%s" + std::to_string(index + 1);
	}

	this->setStringReplacementVariables(localizedStrings);
}

std::string ConcatString::getStringIdentifier() { return "ConcatString"; }

std::string ConcatString::getStringByLanguage(LanguageType languageType)
{
	return this->concatString;
}