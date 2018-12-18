#include "HexusOpponentAjax.h"

const std::string HexusOpponentAjax::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_AJAX";
HexusOpponentAjax* HexusOpponentAjax::instance = nullptr;

HexusOpponentAjax* HexusOpponentAjax::getInstance()
{
	if (HexusOpponentAjax::instance == nullptr)
	{
		HexusOpponentAjax::instance = new HexusOpponentAjax();
	}

	return HexusOpponentAjax::instance;
}

HexusOpponentAjax::HexusOpponentAjax() : HexusOpponentData(
	EntityResources::Npcs_Ajax_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameRuins,
	1.0f,
	Vec2(-48.0f, -64.0f),
	Vec2(-16.0f, -40.0f),
	HexusOpponentAjax::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.26f),
	HexusOpponentData::generateDeck(25, 0.26f,
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

HexusOpponentAjax::~HexusOpponentAjax()
{
}
