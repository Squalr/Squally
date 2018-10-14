#include "HexusOpponentSkeletalBaron.h"

const std::string HexusOpponentSkeletalBaron::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_SKELETAL_BARON";
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
	Vec2(64.0f, -64.0f),
	HexusOpponentSkeletalBaron::OpponentSaveKey,
	HexusOpponentData::Difficulty::Stupid,
	Card::CardStyle::Earth,
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal4),
		CardList::getInstance()->cardListByName->at(CardKeys::LogicalAnd),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex4),
	},
	HexusOpponentData::generateDeck(25, 0, 12, 0.33f, 0.33f,
		{
			CardList::getInstance()->cardListByName->at(CardKeys::Addition),
			CardList::getInstance()->cardListByName->at(CardKeys::LogicalAnd),
			CardList::getInstance()->cardListByName->at(CardKeys::LogicalOr),
			CardList::getInstance()->cardListByName->at(CardKeys::LogicalXor),
			CardList::getInstance()->cardListByName->at(CardKeys::ShiftLeft),
			CardList::getInstance()->cardListByName->at(CardKeys::ShiftRight),
		})
	)
{
}

HexusOpponentSkeletalBaron::~HexusOpponentSkeletalBaron()
{
}
