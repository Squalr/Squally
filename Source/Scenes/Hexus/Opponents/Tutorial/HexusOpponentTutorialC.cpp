#include "HexusOpponentTutorialC.h"

const std::string HexusOpponentTutorialC::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_TUTORIAL_C";
HexusOpponentTutorialC* HexusOpponentTutorialC::instance = nullptr;

HexusOpponentTutorialC* HexusOpponentTutorialC::getInstance()
{
	if (HexusOpponentTutorialC::instance == nullptr)
	{
		HexusOpponentTutorialC::instance = new HexusOpponentTutorialC();
	}

	return HexusOpponentTutorialC::instance;
}

HexusOpponentTutorialC::HexusOpponentTutorialC() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Caverns_Npcs_Alder_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameCaverns,
	0.85f,
	Vec2(-48.0f, -64.0f),
	Vec2(-16.0f, -32.0f),
	HexusOpponentTutorialC::OpponentSaveKey,
	HexusOpponentData::Difficulty::Stupid,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.085f),
	HexusOpponentData::generateDeck(25, 0.085f,
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

HexusOpponentTutorialC::~HexusOpponentTutorialC()
{
}
