#include "HexusOpponentLioness.h"

const std::string HexusOpponentLioness::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_LIONESS";
HexusOpponentLioness* HexusOpponentLioness::instance = nullptr;

HexusOpponentLioness* HexusOpponentLioness::getInstance()
{
	if (HexusOpponentLioness::instance == nullptr)
	{
		HexusOpponentLioness::instance = new HexusOpponentLioness();
	}

	return HexusOpponentLioness::instance;
}

HexusOpponentLioness::HexusOpponentLioness() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Ruins_Enemies_Lioness_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameRuins,
	0.9f,
	Vec2(-48.0f, -64.0f),
	Vec2(-32.0f, -48.0f),
	HexusOpponentLioness::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.215f),
	HexusOpponentData::generateDeck(25, 0.215f,
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

HexusOpponentLioness::~HexusOpponentLioness()
{
}
