#pragma once
#include <string>

#include "Engine/Localization/LocalizedString.h"

class ConcatString : public LocalizedString
{
public:
	static ConcatString* create(std::vector<LocalizedString*> localizedStrings);
	LocalizedString* clone() override;
	std::string getStringIdentifier() override;
	
protected:
	std::string getStringByLanguage(cocos2d::LanguageType languageType) override;
	
private:
	ConcatString(std::vector<LocalizedString*> localizedStrings);
	virtual ~ConcatString() = default;

	std::string concatString;
};