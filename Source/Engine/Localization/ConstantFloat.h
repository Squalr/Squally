#pragma once
#include <string>

#include "Engine/Localization/LocalizedString.h"

class ConstantFloat : public LocalizedString
{
public:
	static ConstantFloat* create(float constantFloat = 0.0f, int precision = 2, bool appendF = true);
	LocalizedString* clone() override;
	std::string getStringIdentifier() override;
	void setValue(float newValue);
	void setPrecision(int precision);
	void setAppendF(bool appendF);

protected:
	ConstantFloat(float constantFloat, int precision, bool appendF);
	virtual ~ConstantFloat();

private:
	typedef LocalizedString super;

	std::string getStringByLanguage(cocos2d::LanguageType languageType) override;

	bool appendF;
	float constantFloat;
	int precision;
};
