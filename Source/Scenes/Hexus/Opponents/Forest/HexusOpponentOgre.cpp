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
	Resources::Entities_Platformer_Environment_Forest_Enemies_Ogre_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameForest,
	1.0f,
	Vec2(-48.0f, -64.0f),
	Vec2(-48.0f, -48.0f),
	HexusOpponentOgre::OpponentSaveKey,
	HexusOpponentData::Difficulty::Stupid,
	Card::CardStyle::Earth,
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal4),
		CardList::getInstance()->cardListByName->at(CardKeys::LogicalAnd),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex4),
	},
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
