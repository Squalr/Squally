////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "Attack.h"

namespace Strings
{
	Combat_Attack* Combat_Attack::create()
	{
		Combat_Attack* instance = new Combat_Attack();

		instance->autorelease();

		return instance;
	}
	
	LocalizedString* Combat_Attack::clone()
	{
		LocalizedString* clonedString = Combat_Attack::create();
		
		this->copyAttributesTo(clonedString);
		
		return clonedString;
	}

	Combat_Attack::Combat_Attack() : LocalizedString()
	{
	}

	Combat_Attack::~Combat_Attack()
	{
	}

	std::string Combat_Attack::getStringIdentifier()
	{
		return "Combat_Attack";
	}

	std::string Combat_Attack::getStringAr()
	{
		return "هجوم";
	}

	std::string Combat_Attack::getStringBg()
	{
		return "атака";
	}

	std::string Combat_Attack::getStringCs()
	{
		return "Záchvat";
	}

	std::string Combat_Attack::getStringDa()
	{
		return "Angreb";
	}

	std::string Combat_Attack::getStringDe()
	{
		return "Attacke";
	}

	std::string Combat_Attack::getStringEl()
	{
		return "Επίθεση";
	}

	std::string Combat_Attack::getStringEn()
	{
		return "Attack";
	}

	std::string Combat_Attack::getStringEs()
	{
		return "Ataque";
	}

	std::string Combat_Attack::getStringEs419()
	{
		return "Ataque";
	}

	std::string Combat_Attack::getStringFi()
	{
		return "Hyökkäys";
	}

	std::string Combat_Attack::getStringFr()
	{
		return "Attaque";
	}

	std::string Combat_Attack::getStringHu()
	{
		return "Támadás";
	}

	std::string Combat_Attack::getStringIt()
	{
		return "attacco";
	}

	std::string Combat_Attack::getStringJa()
	{
		return "攻撃";
	}

	std::string Combat_Attack::getStringKo()
	{
		return "공격";
	}

	std::string Combat_Attack::getStringNl()
	{
		return "Aanval";
	}

	std::string Combat_Attack::getStringNo()
	{
		return "angrep";
	}

	std::string Combat_Attack::getStringPl()
	{
		return "Atak";
	}

	std::string Combat_Attack::getStringPt()
	{
		return "Ataque";
	}

	std::string Combat_Attack::getStringPtBr()
	{
		return "Ataque";
	}

	std::string Combat_Attack::getStringRo()
	{
		return "Atac";
	}

	std::string Combat_Attack::getStringRu()
	{
		return "Атака";
	}

	std::string Combat_Attack::getStringSv()
	{
		return "Ge sig på";
	}

	std::string Combat_Attack::getStringTh()
	{
		return "โจมตี";
	}

	std::string Combat_Attack::getStringTr()
	{
		return "saldırı";
	}

	std::string Combat_Attack::getStringUk()
	{
		return "Атака";
	}

	std::string Combat_Attack::getStringVi()
	{
		return "Tấn công";
	}

	std::string Combat_Attack::getStringZhCn()
	{
		return "攻击";
	}

	std::string Combat_Attack::getStringZhTw()
	{
		return "攻擊";
	}
}
