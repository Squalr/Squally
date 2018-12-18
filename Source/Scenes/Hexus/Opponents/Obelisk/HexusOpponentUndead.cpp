#include "HexusOpponentUndead.h"

const std::string HexusOpponentUndead::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_UNDEAD";
HexusOpponentUndead* HexusOpponentUndead::instance = nullptr;

HexusOpponentUndead* HexusOpponentUndead::getInstance()
{
	if (HexusOpponentUndead::instance == nullptr)
	{
		HexusOpponentUndead::instance = new HexusOpponentUndead();
	}

	return HexusOpponentUndead::instance;
}

HexusOpponentUndead::HexusOpponentUndead() : HexusOpponentData(
	EntityResources::Enemies_LexiconCrypts_Undead_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameObelisk,
	0.9f,
	Vec2(-48.0f, -64.0f),
	Vec2(-16.0f, -40.0f),
	HexusOpponentUndead::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.835f),
	HexusOpponentData::generateDeck(25, 0.835f,
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

HexusOpponentUndead::~HexusOpponentUndead()
{
}
