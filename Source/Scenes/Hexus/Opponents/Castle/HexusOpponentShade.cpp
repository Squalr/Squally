#include "HexusOpponentShade.h"

const std::string HexusOpponentShade::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_SHADE";
HexusOpponentShade* HexusOpponentShade::instance = nullptr;

HexusOpponentShade* HexusOpponentShade::getInstance()
{
	if (HexusOpponentShade::instance == nullptr)
	{
		HexusOpponentShade::instance = new HexusOpponentShade();
	}

	return HexusOpponentShade::instance;
}

HexusOpponentShade::HexusOpponentShade() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Castle_Enemies_Shade_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameCastle,
	1.0f,
	Vec2(-32.0f, -96.0f),
	Vec2(-16.0f, -128.0f),
	HexusOpponentShade::OpponentSaveKey,
	HexusOpponentData::Difficulty::Stupid,
	Card::CardStyle::Shadow,
	HexusOpponentData::generateReward(0.595f),
	HexusOpponentData::generateDeck(25, 0.595f,
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

HexusOpponentShade::~HexusOpponentShade()
{
}
