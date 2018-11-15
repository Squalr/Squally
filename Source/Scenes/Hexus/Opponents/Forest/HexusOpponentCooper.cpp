#include "HexusOpponentCooper.h"

const std::string HexusOpponentCooper::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_COOPER";
HexusOpponentCooper* HexusOpponentCooper::instance = nullptr;

HexusOpponentCooper* HexusOpponentCooper::getInstance()
{
	if (HexusOpponentCooper::instance == nullptr)
	{
		HexusOpponentCooper::instance = new HexusOpponentCooper();
	}

	return HexusOpponentCooper::instance;
}

HexusOpponentCooper::HexusOpponentCooper() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Forest_Npcs_Cooper_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameForest,
	1.0f,
	Vec2(-48.0f, -48.0f),
	Vec2(-16.0f, -24.0f),
	HexusOpponentCooper::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.33f),
	HexusOpponentData::generateDeck(25, 0.33f,
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

HexusOpponentCooper::~HexusOpponentCooper()
{
}
