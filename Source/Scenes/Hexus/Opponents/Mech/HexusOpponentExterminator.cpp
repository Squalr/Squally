#include "HexusOpponentExterminator.h"

const std::string HexusOpponentExterminator::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_EXTERMINATOR";
HexusOpponentExterminator* HexusOpponentExterminator::instance = nullptr;

HexusOpponentExterminator* HexusOpponentExterminator::getInstance()
{
	if (HexusOpponentExterminator::instance == nullptr)
	{
		HexusOpponentExterminator::instance = new HexusOpponentExterminator();
	}

	return HexusOpponentExterminator::instance;
}

HexusOpponentExterminator::HexusOpponentExterminator() : HexusOpponentData(
	EntityResources::Platformer_Environment_Mech_Enemies_Exterminator_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameMech,
	1.0f,
	Vec2(-48.0f, -64.0f),
	Vec2(-48.0f, -64.0f),
	HexusOpponentExterminator::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.965f),
	HexusOpponentData::generateDeck(25, 0.965f,
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

HexusOpponentExterminator::~HexusOpponentExterminator()
{
}
