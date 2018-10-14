#include "HexusOpponentSkeletalPirate.h"

const std::string HexusOpponentSkeletalPirate::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_SKELETAL_PIRATE";
HexusOpponentSkeletalPirate* HexusOpponentSkeletalPirate::instance = nullptr;

HexusOpponentSkeletalPirate* HexusOpponentSkeletalPirate::getInstance()
{
	if (HexusOpponentSkeletalPirate::instance == nullptr)
	{
		HexusOpponentSkeletalPirate::instance = new HexusOpponentSkeletalPirate();
	}

	return HexusOpponentSkeletalPirate::instance;
}

HexusOpponentSkeletalPirate::HexusOpponentSkeletalPirate() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Jungle_Enemies_SkeletalPirate_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameJungle,
	0.8f,
	Vec2(-48.0f, -80.0f),
	Vec2(-16.0f, -64.0f),
	HexusOpponentSkeletalPirate::OpponentSaveKey,
	HexusOpponentData::Difficulty::Stupid,
	Card::CardStyle::Earth,
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal3),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal2),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal1),
	},
	HexusOpponentData::generateDeck(25, 0, 5, 0.33f, 0.33f,
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

HexusOpponentSkeletalPirate::~HexusOpponentSkeletalPirate()
{
}
