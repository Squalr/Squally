#include "HexusOpponentOgre.h"

const std::string HexusOpponentOgre::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_OGRE";
HexusOpponentOgre* HexusOpponentOgre::instance = nullptr;

HexusOpponentOgre* HexusOpponentOgre::getInstance()
{
	if (HexusOpponentOgre::instance == nullptr)
	{
		HexusOpponentOgre::instance = new HexusOpponentOgre();
	}

	return HexusOpponentOgre::instance;
}

HexusOpponentOgre::HexusOpponentOgre() : HexusOpponentData(
	EntityResources::Platformer_Environment_Forest_Enemies_Ogre_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameForest,
	1.0f,
	Vec2(-48.0f, -64.0f),
	Vec2(-48.0f, -48.0f),
	HexusOpponentOgre::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.395f),
	HexusOpponentData::generateDeck(25, 0.395f,
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

HexusOpponentOgre::~HexusOpponentOgre()
{
}
