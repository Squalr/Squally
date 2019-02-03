////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "Items.h"

namespace Strings
{
	Combat_Items* Combat_Items::create()
	{
		Combat_Items* instance = new Combat_Items();

		instance->autorelease();

		return instance;
	}
	
	LocalizedString* Combat_Items::clone()
	{
		LocalizedString* clonedString = Combat_Items::create();
		
		this->copyAttributesTo(clonedString);
		
		return clonedString;
	}

	Combat_Items::Combat_Items() : LocalizedString()
	{
	}

	Combat_Items::~Combat_Items()
	{
	}

	std::string Combat_Items::getStringIdentifier()
	{
		return "Combat_Items";
	}

	std::string Combat_Items::getStringAr()
	{
		return "العناصر";
	}

	std::string Combat_Items::getStringBg()
	{
		return "Предмети";
	}

	std::string Combat_Items::getStringCs()
	{
		return "Položky";
	}

	std::string Combat_Items::getStringDa()
	{
		return "Elementer";
	}

	std::string Combat_Items::getStringDe()
	{
		return "Artikel";
	}

	std::string Combat_Items::getStringEl()
	{
		return "Στοιχεία";
	}

	std::string Combat_Items::getStringEn()
	{
		return "Items";
	}

	std::string Combat_Items::getStringEs()
	{
		return "Artículos";
	}

	std::string Combat_Items::getStringEs419()
	{
		return "Artículos";
	}

	std::string Combat_Items::getStringFi()
	{
		return "Tuotteet";
	}

	std::string Combat_Items::getStringFr()
	{
		return "Articles";
	}

	std::string Combat_Items::getStringHu()
	{
		return "példány";
	}

	std::string Combat_Items::getStringIt()
	{
		return "Elementi";
	}

	std::string Combat_Items::getStringJa()
	{
		return "アイテム";
	}

	std::string Combat_Items::getStringKo()
	{
		return "항목";
	}

	std::string Combat_Items::getStringNl()
	{
		return "items";
	}

	std::string Combat_Items::getStringNo()
	{
		return "elementer";
	}

	std::string Combat_Items::getStringPl()
	{
		return "Przedmiotów";
	}

	std::string Combat_Items::getStringPt()
	{
		return "Unid";
	}

	std::string Combat_Items::getStringPtBr()
	{
		return "Unid";
	}

	std::string Combat_Items::getStringRo()
	{
		return "Articole";
	}

	std::string Combat_Items::getStringRu()
	{
		return "Предметы";
	}

	std::string Combat_Items::getStringSv()
	{
		return "artiklar";
	}

	std::string Combat_Items::getStringTh()
	{
		return "รายการ";
	}

	std::string Combat_Items::getStringTr()
	{
		return "Öğeler";
	}

	std::string Combat_Items::getStringUk()
	{
		return "Елементи";
	}

	std::string Combat_Items::getStringVi()
	{
		return "Mặt hàng";
	}

	std::string Combat_Items::getStringZhCn()
	{
		return "项目";
	}

	std::string Combat_Items::getStringZhTw()
	{
		return "項目";
	}
}
