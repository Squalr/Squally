#include "ConstantString.h"

using namespace cocos2d;

ConstantString* ConstantString::create(std::string constantString)
{
	ConstantString* instance = new ConstantString(constantString);

	instance->autorelease();

	return instance;
}

ConstantString::ConstantString(std::string constantString)
{
	this->constantString = constantString;
}

ConstantString::~ConstantString()
{
}

LocalizedString* ConstantString::clone()
{
	return ConstantString::create(this->constantString);
}

void ConstantString::setString(std::string newString)
{
	this->constantString = newString;

	if (this->onStringUpdate != nullptr)
	{
		this->onStringUpdate();
	}
}

std::string ConstantString::getStringIdentifier()
{
	return "ConstantString";
}

std::string ConstantString::getStringByLanguage(LanguageType languageType)
{
	return this->constantString;
}
