#include "HexusOpponentVoidDemon.h"

const std::string HexusOpponentVoidDemon::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_VOID_DEMON";
HexusOpponentVoidDemon* HexusOpponentVoidDemon::instance = nullptr;

HexusOpponentVoidDemon* HexusOpponentVoidDemon::getInstance()
{
	if (HexusOpponentVoidDemon::instance == nullptr)
	{
		HexusOpponentVoidDemon::instance = new HexusOpponentVoidDemon();
	}

	return HexusOpponentVoidDemon::instance;
}

HexusOpponentVoidDemon::HexusOpponentVoidDemon() : HexusOpponentData(
	EntityResources::Platformer_Environment_Obelisk_Enemies_VoidDemon_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameObelisk,
	0.7f,
	Vec2(-48.0f, -24.0f),
	Vec2(-48.0f, -8.0f),
	HexusOpponentVoidDemon::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.805f),
	HexusOpponentData::generateDeck(25, 0.805f,
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

HexusOpponentVoidDemon::~HexusOpponentVoidDemon()
{
}
