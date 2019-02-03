////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "Skills.h"

namespace Strings
{
	Combat_Skills* Combat_Skills::create()
	{
		Combat_Skills* instance = new Combat_Skills();

		instance->autorelease();

		return instance;
	}
	
	LocalizedString* Combat_Skills::clone()
	{
		LocalizedString* clonedString = Combat_Skills::create();
		
		this->copyAttributesTo(clonedString);
		
		return clonedString;
	}

	Combat_Skills::Combat_Skills() : LocalizedString()
	{
	}

	Combat_Skills::~Combat_Skills()
	{
	}

	std::string Combat_Skills::getStringIdentifier()
	{
		return "Combat_Skills";
	}

	std::string Combat_Skills::getStringAr()
	{
		return "مهارات";
	}

	std::string Combat_Skills::getStringBg()
	{
		return "умения";
	}

	std::string Combat_Skills::getStringCs()
	{
		return "Dovednosti";
	}

	std::string Combat_Skills::getStringDa()
	{
		return "Skills";
	}

	std::string Combat_Skills::getStringDe()
	{
		return "Kompetenzen";
	}

	std::string Combat_Skills::getStringEl()
	{
		return "Δεξιότητες";
	}

	std::string Combat_Skills::getStringEn()
	{
		return "Skills";
	}

	std::string Combat_Skills::getStringEs()
	{
		return "Habilidades";
	}

	std::string Combat_Skills::getStringEs419()
	{
		return "Habilidades";
	}

	std::string Combat_Skills::getStringFi()
	{
		return "Skills";
	}

	std::string Combat_Skills::getStringFr()
	{
		return "Compétences";
	}

	std::string Combat_Skills::getStringHu()
	{
		return "szakértelem";
	}

	std::string Combat_Skills::getStringIt()
	{
		return "Abilità";
	}

	std::string Combat_Skills::getStringJa()
	{
		return "スキル";
	}

	std::string Combat_Skills::getStringKo()
	{
		return "기술";
	}

	std::string Combat_Skills::getStringNl()
	{
		return "Vaardigheden";
	}

	std::string Combat_Skills::getStringNo()
	{
		return "ferdigheter";
	}

	std::string Combat_Skills::getStringPl()
	{
		return "Umiejętności";
	}

	std::string Combat_Skills::getStringPt()
	{
		return "Habilidades";
	}

	std::string Combat_Skills::getStringPtBr()
	{
		return "Habilidades";
	}

	std::string Combat_Skills::getStringRo()
	{
		return "Aptitudini";
	}

	std::string Combat_Skills::getStringRu()
	{
		return "Навыки";
	}

	std::string Combat_Skills::getStringSv()
	{
		return "Kompetens";
	}

	std::string Combat_Skills::getStringTh()
	{
		return "ทักษะ";
	}

	std::string Combat_Skills::getStringTr()
	{
		return "Beceri";
	}

	std::string Combat_Skills::getStringUk()
	{
		return "Навички";
	}

	std::string Combat_Skills::getStringVi()
	{
		return "Kỹ năng";
	}

	std::string Combat_Skills::getStringZhCn()
	{
		return "技能";
	}

	std::string Combat_Skills::getStringZhTw()
	{
		return "技能";
	}
}
