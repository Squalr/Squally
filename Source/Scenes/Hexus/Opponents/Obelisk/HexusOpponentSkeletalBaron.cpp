#include "HexusOpponentSkeletalBaron.h"

const std::string HexusOpponentSkeletalBaron::StringKeyOpponentName = "Squally_Npc_Names_Skeletal_Baron";
HexusOpponentSkeletalBaron* HexusOpponentSkeletalBaron::instance = nullptr;

HexusOpponentSkeletalBaron* HexusOpponentSkeletalBaron::getInstance()
{
	if (HexusOpponentSkeletalBaron::instance == nullptr)
	{
		HexusOpponentSkeletalBaron::instance = new HexusOpponentSkeletalBaron();
	}

	return HexusOpponentSkeletalBaron::instance;
}

HexusOpponentSkeletalBaron::HexusOpponentSkeletalBaron() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Obelisk_Enemies_SkeletalBaron_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameObelisk,
	0.85f,
	Vec2(48.0f, -64.0f),
	Vec2(-16.0f, -48.0f),
	HexusOpponentSkeletalBaron::StringKeyOpponentName,
	HexusOpponentData::Difficulty::Stupid,
	Card::CardStyle::Earth,
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal4),
		CardList::getInstance()->cardListByName->at(CardKeys::LogicalAnd),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex4),
	},
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Binary0),
		CardList::getInstance()->cardListByName->at(CardKeys::Binary1),
		CardList::getInstance()->cardListByName->at(CardKeys::Binary3),
		CardList::getInstance()->cardListByName->at(CardKeys::Binary3),
		CardList::getInstance()->cardListByName->at(CardKeys::Binary4),
		CardList::getInstance()->cardListByName->at(CardKeys::Binary4),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal0),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal1),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal3),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal3),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal4),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal5),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex0),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex2),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex3),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex3),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex4),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex5),
		CardList::getInstance()->cardListByName->at(CardKeys::Addition),
		CardList::getInstance()->cardListByName->at(CardKeys::LogicalAnd),
		CardList::getInstance()->cardListByName->at(CardKeys::LogicalOr),
		CardList::getInstance()->cardListByName->at(CardKeys::LogicalXor),
		CardList::getInstance()->cardListByName->at(CardKeys::ShiftLeft),
		CardList::getInstance()->cardListByName->at(CardKeys::ShiftRight),
	})
{
}

HexusOpponentSkeletalBaron::~HexusOpponentSkeletalBaron()
{
}
