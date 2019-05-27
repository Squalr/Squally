////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "Defeat.h"

namespace Strings
{
	Combat_Defeat* Combat_Defeat::create()
	{
		Combat_Defeat* instance = new Combat_Defeat();

		instance->autorelease();

		return instance;
	}
	
	LocalizedString* Combat_Defeat::clone()
	{
		LocalizedString* clonedString = Combat_Defeat::create();
		
		this->copyAttributesTo(clonedString);
		
		return clonedString;
	}

	Combat_Defeat::Combat_Defeat() : LocalizedString()
	{
	}

	Combat_Defeat::~Combat_Defeat()
	{
	}

	std::string Combat_Defeat::getStringIdentifier()
	{
		return "Combat_Defeat";
	}

	std::string Combat_Defeat::getStringAr()
	{
		return "هزيمة!";
	}

	std::string Combat_Defeat::getStringBg()
	{
		return "Поражение!";
	}

	std::string Combat_Defeat::getStringCs()
	{
		return "PORAZIT!";
	}

	std::string Combat_Defeat::getStringDa()
	{
		return "NEDERLAG!";
	}

	std::string Combat_Defeat::getStringDe()
	{
		return "NIEDERLAGE!";
	}

	std::string Combat_Defeat::getStringEl()
	{
		return "ΗΤΤΑ!";
	}

	std::string Combat_Defeat::getStringEn()
	{
		return "DEFEAT!";
	}

	std::string Combat_Defeat::getStringEs()
	{
		return "¡DERROTA!";
	}

	std::string Combat_Defeat::getStringEs419()
	{
		return "¡DERROTA!";
	}

	std::string Combat_Defeat::getStringFi()
	{
		return "VOITTAA!";
	}

	std::string Combat_Defeat::getStringFr()
	{
		return "DÉFAITE!";
	}

	std::string Combat_Defeat::getStringHu()
	{
		return "VERESÉG!";
	}

	std::string Combat_Defeat::getStringIt()
	{
		return "LA SCONFITTA!";
	}

	std::string Combat_Defeat::getStringJa()
	{
		return "敗北！";
	}

	std::string Combat_Defeat::getStringKo()
	{
		return "패배!";
	}

	std::string Combat_Defeat::getStringNl()
	{
		return "NEDERLAAG!";
	}

	std::string Combat_Defeat::getStringNo()
	{
		return "NEDERLAG!";
	}

	std::string Combat_Defeat::getStringPl()
	{
		return "POKONAĆ!";
	}

	std::string Combat_Defeat::getStringPt()
	{
		return "DERROTA!";
	}

	std::string Combat_Defeat::getStringPtBr()
	{
		return "DERROTA!";
	}

	std::string Combat_Defeat::getStringRo()
	{
		return "ÎNFRÂNGERE!";
	}

	std::string Combat_Defeat::getStringRu()
	{
		return "ПОРАЖЕНИЕ!";
	}

	std::string Combat_Defeat::getStringSv()
	{
		return "NEDERLAG!";
	}

	std::string Combat_Defeat::getStringTh()
	{
		return "พ่ายแพ้!";
	}

	std::string Combat_Defeat::getStringTr()
	{
		return "YENİLGİ!";
	}

	std::string Combat_Defeat::getStringUk()
	{
		return "ПОРУШЕННЯ!";
	}

	std::string Combat_Defeat::getStringVi()
	{
		return "ĐÁNH BẠI!";
	}

	std::string Combat_Defeat::getStringZhCn()
	{
		return "打败！";
	}

	std::string Combat_Defeat::getStringZhTw()
	{
		return "打敗！";
	}
}
