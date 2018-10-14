#include "HexusOpponentDemonSwordsman.h"

const std::string HexusOpponentDemonSwordsman::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_DEMON_SWORDSMAN";
HexusOpponentDemonSwordsman* HexusOpponentDemonSwordsman::instance = nullptr;

HexusOpponentDemonSwordsman* HexusOpponentDemonSwordsman::getInstance()
{
	if (HexusOpponentDemonSwordsman::instance == nullptr)
	{
		HexusOpponentDemonSwordsman::instance = new HexusOpponentDemonSwordsman();
	}

	return HexusOpponentDemonSwordsman::instance;
}

HexusOpponentDemonSwordsman::HexusOpponentDemonSwordsman() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Volcano_Enemies_DemonSwordsman_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameVolcano,
	0.85f,
	Vec2(-48.0f, -48.0f),
	Vec2(-24.0f, -48.0f),
	HexusOpponentDemonSwordsman::OpponentSaveKey,
	HexusOpponentData::Difficulty::Stupid,
	Card::CardStyle::Earth,
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal4),
		CardList::getInstance()->cardListByName->at(CardKeys::LogicalAnd),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex4),
	},
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Binary0),
		CardList::getInstance()->cardListByName->at(CardKeys::Binary1),
		CardList::getInstance()->cardListByName->at(CardKeys::Binary3),
		CardList::getInstance()->cardListByName->at(CardKeys::Binary3),
		CardList::getInstance()->cardListByName->at(CardKeys::Binary4),
		CardList::getInstance()->cardListByName->at(CardKeys::Binary4),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal0),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal1),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal3),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal3),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal4),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal5),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex0),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex2),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex3),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex3),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex4),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex5),
		CardList::getInstance()->cardListByName->at(CardKeys::Addition),
		CardList::getInstance()->cardListByName->at(CardKeys::LogicalAnd),
		CardList::getInstance()->cardListByName->at(CardKeys::LogicalOr),
		CardList::getInstance()->cardListByName->at(CardKeys::LogicalXor),
		CardList::getInstance()->cardListByName->at(CardKeys::ShiftLeft),
		CardList::getInstance()->cardListByName->at(CardKeys::ShiftRight),
	})
{
}

HexusOpponentDemonSwordsman::~HexusOpponentDemonSwordsman()
{
}
