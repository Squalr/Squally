////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "Spells.h"

namespace Strings
{
	Combat_Spells* Combat_Spells::create()
	{
		Combat_Spells* instance = new Combat_Spells();

		instance->autorelease();

		return instance;
	}
	
	LocalizedString* Combat_Spells::clone()
	{
		LocalizedString* clonedString = Combat_Spells::create();
		
		this->copyAttributesTo(clonedString);
		
		return clonedString;
	}

	Combat_Spells::Combat_Spells() : LocalizedString()
	{
	}

	Combat_Spells::~Combat_Spells()
	{
	}

	std::string Combat_Spells::getStringIdentifier()
	{
		return "Combat_Spells";
	}

	std::string Combat_Spells::getStringAr()
	{
		return "نوبات";
	}

	std::string Combat_Spells::getStringBg()
	{
		return "магии";
	}

	std::string Combat_Spells::getStringCs()
	{
		return "Kouzla";
	}

	std::string Combat_Spells::getStringDa()
	{
		return "spells";
	}

	std::string Combat_Spells::getStringDe()
	{
		return "Zaubersprüche";
	}

	std::string Combat_Spells::getStringEl()
	{
		return "Ξόρκια";
	}

	std::string Combat_Spells::getStringEn()
	{
		return "Spells";
	}

	std::string Combat_Spells::getStringEs()
	{
		return "Hechizos";
	}

	std::string Combat_Spells::getStringEs419()
	{
		return "Hechizos";
	}

	std::string Combat_Spells::getStringFi()
	{
		return "loitsuja";
	}

	std::string Combat_Spells::getStringFr()
	{
		return "Sorts";
	}

	std::string Combat_Spells::getStringHu()
	{
		return "varázslatok";
	}

	std::string Combat_Spells::getStringIt()
	{
		return "incantesimi";
	}

	std::string Combat_Spells::getStringJa()
	{
		return "呪文";
	}

	std::string Combat_Spells::getStringKo()
	{
		return "주문";
	}

	std::string Combat_Spells::getStringNl()
	{
		return "spells";
	}

	std::string Combat_Spells::getStringNo()
	{
		return "spells";
	}

	std::string Combat_Spells::getStringPl()
	{
		return "Czary";
	}

	std::string Combat_Spells::getStringPt()
	{
		return "Feitiços";
	}

	std::string Combat_Spells::getStringPtBr()
	{
		return "Feitiços";
	}

	std::string Combat_Spells::getStringRo()
	{
		return "vrăji";
	}

	std::string Combat_Spells::getStringRu()
	{
		return "Заклинания";
	}

	std::string Combat_Spells::getStringSv()
	{
		return "spells";
	}

	std::string Combat_Spells::getStringTh()
	{
		return "คาถา";
	}

	std::string Combat_Spells::getStringTr()
	{
		return "büyüler";
	}

	std::string Combat_Spells::getStringUk()
	{
		return "Заклинання";
	}

	std::string Combat_Spells::getStringVi()
	{
		return "Phép thuật";
	}

	std::string Combat_Spells::getStringZhCn()
	{
		return "法术";
	}

	std::string Combat_Spells::getStringZhTw()
	{
		return "法術";
	}
}
