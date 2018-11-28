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
	EntityResources::Environment_Jungle_Enemies_SkeletalPirate_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameJungle,
	0.8f,
	Vec2(-48.0f, -80.0f),
	Vec2(-16.0f, -64.0f),
	HexusOpponentSkeletalPirate::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.17f),
	HexusOpponentData::generateDeck(25, 0.17f,
		{
			CardList::getInstance()->cardListByName->at(CardKeys::Binary0),
			CardList::getInstance()->cardListByName->at(CardKeys::Hex0),
			CardList::getInstance()->cardListByName->at(CardKeys::Decimal0),
			CardList::getInstance()->cardListByName->at(CardKeys::Addition),
			CardList::getInstance()->cardListByName->at(CardKeys::Addition),
			CardList::getInstance()->cardListByName->at(CardKeys::ShiftLeft),
			CardList::getInstance()->cardListByName->at(CardKeys::ShiftRight),
		})
	)
{
}

HexusOpponentSkeletalPirate::~HexusOpponentSkeletalPirate()
{
}
