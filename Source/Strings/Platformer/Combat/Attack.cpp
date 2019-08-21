////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "Attack.h"

namespace Strings
{
	Platformer_Combat_Attack* Platformer_Combat_Attack::create()
	{
		Platformer_Combat_Attack* instance = new Platformer_Combat_Attack();

		instance->autorelease();

		return instance;
	}
	
	LocalizedString* Platformer_Combat_Attack::clone()
	{
		LocalizedString* clonedString = Platformer_Combat_Attack::create();
		
		this->copyAttributesTo(clonedString);
		
		return clonedString;
	}

	Platformer_Combat_Attack::Platformer_Combat_Attack() : LocalizedString()
	{
	}

	Platformer_Combat_Attack::~Platformer_Combat_Attack()
	{
	}

	std::string Platformer_Combat_Attack::getStringIdentifier()
	{
		return "Platformer_Combat_Attack";
	}

	std::string Platformer_Combat_Attack::getStringAr()
	{
		return "هجوم";
	}

	std::string Platformer_Combat_Attack::getStringBg()
	{
		return "атака";
	}

	std::string Platformer_Combat_Attack::getStringCs()
	{
		return "Záchvat";
	}

	std::string Platformer_Combat_Attack::getStringDa()
	{
		return "Angreb";
	}

	std::string Platformer_Combat_Attack::getStringDe()
	{
		return "Attacke";
	}

	std::string Platformer_Combat_Attack::getStringEl()
	{
		return "Επίθεση";
	}

	std::string Platformer_Combat_Attack::getStringEn()
	{
		return "Attack";
	}

	std::string Platformer_Combat_Attack::getStringEs()
	{
		return "Ataque";
	}

	std::string Platformer_Combat_Attack::getStringEs419()
	{
		return "Ataque";
	}

	std::string Platformer_Combat_Attack::getStringFi()
	{
		return "Hyökkäys";
	}

	std::string Platformer_Combat_Attack::getStringFr()
	{
		return "Attaque";
	}

	std::string Platformer_Combat_Attack::getStringHu()
	{
		return "Támadás";
	}

	std::string Platformer_Combat_Attack::getStringIt()
	{
		return "attacco";
	}

	std::string Platformer_Combat_Attack::getStringJa()
	{
		return "攻撃";
	}

	std::string Platformer_Combat_Attack::getStringKo()
	{
		return "공격";
	}

	std::string Platformer_Combat_Attack::getStringNl()
	{
		return "Aanval";
	}

	std::string Platformer_Combat_Attack::getStringNo()
	{
		return "angrep";
	}

	std::string Platformer_Combat_Attack::getStringPl()
	{
		return "Atak";
	}

	std::string Platformer_Combat_Attack::getStringPt()
	{
		return "Ataque";
	}

	std::string Platformer_Combat_Attack::getStringPtBr()
	{
		return "Ataque";
	}

	std::string Platformer_Combat_Attack::getStringRo()
	{
		return "Atac";
	}

	std::string Platformer_Combat_Attack::getStringRu()
	{
		return "Атака";
	}

	std::string Platformer_Combat_Attack::getStringSv()
	{
		return "Ge sig på";
	}

	std::string Platformer_Combat_Attack::getStringTh()
	{
		return "โจมตี";
	}

	std::string Platformer_Combat_Attack::getStringTr()
	{
		return "saldırı";
	}

	std::string Platformer_Combat_Attack::getStringUk()
	{
		return "Атака";
	}

	std::string Platformer_Combat_Attack::getStringVi()
	{
		return "Tấn công";
	}

	std::string Platformer_Combat_Attack::getStringZhCn()
	{
		return "攻击";
	}

	std::string Platformer_Combat_Attack::getStringZhTw()
	{
		return "攻擊";
	}
}
