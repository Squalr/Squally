#pragma once
#include <string>

#include "Engine/Localization/LocalizedString.h"

class ConstantString : public LocalizedString
{
public:
	static ConstantString* create(std::string constantString = "");
	LocalizedString* clone() override;
	void setString(std::string newString);
	std::string getStringIdentifier() override;

protected:
	ConstantString(std::string constantString);
	virtual ~ConstantString();

private:
	typedef LocalizedString super;

	std::string getStringByLanguage(cocos2d::LanguageType languageType) override;

	std::string constantString;
};
