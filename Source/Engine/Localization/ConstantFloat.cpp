#include "ConstantFloat.h"

#include <iomanip>
#include <sstream>

#include "Engine/Utils/StrUtils.h"

using namespace cocos2d;

ConstantFloat* ConstantFloat::create(float constantFloat, int precision, bool appendF)
{
	ConstantFloat* instance = new ConstantFloat(constantFloat, precision, appendF);

	instance->autorelease();

	return instance;
}

ConstantFloat::ConstantFloat(float constantFloat, int precision, bool appendF)
{
	this->constantFloat = constantFloat;
	this->precision = precision;
	this->appendF = appendF;
}

ConstantFloat::~ConstantFloat()
{
}

LocalizedString* ConstantFloat::clone()
{
	return ConstantFloat::create(this->constantFloat);
}

void ConstantFloat::setPrecision(int precision)
{
	this->precision = precision;

	if (this->onStringUpdate != nullptr)
	{
		this->onStringUpdate();
	}
}

void ConstantFloat::setAppendF(bool appendF)
{
	this->appendF = appendF;

	if (this->onStringUpdate != nullptr)
	{
		this->onStringUpdate();
	}
}

void ConstantFloat::setValue(float newValue)
{
	this->constantFloat = newValue;

	if (this->onStringUpdate != nullptr)
	{
		this->onStringUpdate();
	}
}

std::string ConstantFloat::getStringIdentifier()
{
	return "ConstantFloat";
}

std::string ConstantFloat::getStringByLanguage(LanguageType languageType)
{
	std::stringstream stream = std::stringstream();

	stream << std::fixed << std::setprecision(this->precision) << this->constantFloat;

	std::string str = stream.str() + (this->appendF ? "f" : "");

	switch (languageType)
	{
		case LanguageType::BULGARIAN:
		case LanguageType::CZECH:
		case LanguageType::DANISH:
		case LanguageType::DUTCH:
		case LanguageType::FRENCH:
		case LanguageType::GERMAN:
		case LanguageType::HUNGARIAN:
		case LanguageType::ITALIAN:
		case LanguageType::NORWEGIAN:
		case LanguageType::POLISH:
		case LanguageType::PORTUGUESE:
		case LanguageType::PORTUGUESE_BRAZIL:
		case LanguageType::ROMANIAN:
		case LanguageType::RUSSIAN:
		case LanguageType::SWEDISH:
		case LanguageType::UKRAINIAN:		
		case LanguageType::VIETNAMESE:
		{
			// These languages use a different format for decimal numbers
			str = StrUtils::replaceFirstOccurence(str, ".", ",");
			break;
		}
		default:
		case LanguageType::ENGLISH:
		case LanguageType::ARABIC:
		case LanguageType::GREEK:
		case LanguageType::SPANISH:
		case LanguageType::SPANISH_LATIN_AMERICAN:
		case LanguageType::FINNISH:
		case LanguageType::JAPANESE:
		case LanguageType::KOREAN:
		case LanguageType::THAI:
		case LanguageType::TURKISH:
		case LanguageType::CHINESE_SIMPLIFIED:
		case LanguageType::CHINESE_TRADITIONAL:
		{
			break;
		}
	}

	return str;
}
