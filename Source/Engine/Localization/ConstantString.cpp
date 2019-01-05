#include "ConstantString.h"

ConstantString* ConstantString::create()
{
	return ConstantString::create("");
}

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

LocalizedString* ConstantString::clone()
{
	return ConstantString::create(this->constantString);
}

void ConstantString::setString(std::string newString)
{
	this->constantString = newString;

	if (this->onStringUpdate != nullptr)
	{
		this->onStringUpdate(this);
	}
}

std::string ConstantString::getStringIdentifier()
{
	return "ConstantString";
}

std::string ConstantString::getStringAr()
{
	return this->constantString;
}

std::string ConstantString::getStringBg()
{
	return this->constantString;
}

std::string ConstantString::getStringCs()
{
	return this->constantString;
}

std::string ConstantString::getStringDa()
{
	return this->constantString;
}

std::string ConstantString::getStringDe()
{
	return this->constantString;
}

std::string ConstantString::getStringEl()
{
	return this->constantString;
}

std::string ConstantString::getStringEn()
{
	return this->constantString;
}

std::string ConstantString::getStringEs()
{
	return this->constantString;
}

std::string ConstantString::getStringEs419()
{
	return this->constantString;
}

std::string ConstantString::getStringFi()
{
	return this->constantString;
}

std::string ConstantString::getStringFr()
{
	return this->constantString;
}

std::string ConstantString::getStringHu()
{
	return this->constantString;
}

std::string ConstantString::getStringIt()
{
	return this->constantString;
}

std::string ConstantString::getStringJa()
{
	return this->constantString;
}

std::string ConstantString::getStringKo()
{
	return this->constantString;
}

std::string ConstantString::getStringNl()
{
	return this->constantString;
}

std::string ConstantString::getStringNo()
{
	return this->constantString;
}

std::string ConstantString::getStringPl()
{
	return this->constantString;
}

std::string ConstantString::getStringPt()
{
	return this->constantString;
}

std::string ConstantString::getStringPtBr()
{
	return this->constantString;
}

std::string ConstantString::getStringRo()
{
	return this->constantString;
}

std::string ConstantString::getStringRu()
{
	return this->constantString;
}

std::string ConstantString::getStringSv()
{
	return this->constantString;
}

std::string ConstantString::getStringTh()
{
	return this->constantString;
}

std::string ConstantString::getStringTr()
{
	return this->constantString;
}

std::string ConstantString::getStringUk()
{
	return this->constantString;
}

std::string ConstantString::getStringVi()
{
	return this->constantString;
}

std::string ConstantString::getStringZhCn()
{
	return this->constantString;
}

std::string ConstantString::getStringZhTw()
{
	return this->constantString;
}
