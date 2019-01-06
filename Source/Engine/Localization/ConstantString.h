#pragma once
#include <string>

#include "Engine/Localization/LocalizedString.h"

class ConstantString : public LocalizedString
{
public:
	static ConstantString* create();
	static ConstantString* create(std::string constantString);
	LocalizedString* clone() override;
	void setString(std::string newString);
	std::string getStringIdentifier() override;

private:
	typedef LocalizedString super;

	ConstantString(std::string constantString);
	~ConstantString() = default;

	std::string getStringAr() override;
	std::string getStringBg() override;
	std::string getStringCs() override;
	std::string getStringDa() override;
	std::string getStringDe() override;
	std::string getStringEl() override;
	std::string getStringEn() override;
	std::string getStringEs() override;
	std::string getStringEs419() override;
	std::string getStringFi() override;
	std::string getStringFr() override;
	std::string getStringHu() override;
	std::string getStringIt() override;
	std::string getStringJa() override;
	std::string getStringKo() override;
	std::string getStringNl() override;
	std::string getStringNo() override;
	std::string getStringPl() override;
	std::string getStringPt() override;
	std::string getStringPtBr() override;
	std::string getStringRo() override;
	std::string getStringRu() override;
	std::string getStringSv() override;
	std::string getStringTh() override;
	std::string getStringTr() override;
	std::string getStringUk() override;
	std::string getStringVi() override;
	std::string getStringZhCn() override;
	std::string getStringZhTw() override;

	std::string constantString;
};
