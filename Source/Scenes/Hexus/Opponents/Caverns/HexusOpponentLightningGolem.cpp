#include "HexusOpponentLightningGolem.h"

const std::string HexusOpponentLightningGolem::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_LIGHTNING_GOLEM";
HexusOpponentLightningGolem* HexusOpponentLightningGolem::instance = nullptr;

HexusOpponentLightningGolem* HexusOpponentLightningGolem::getInstance()
{
	if (HexusOpponentLightningGolem::instance == nullptr)
	{
		HexusOpponentLightningGolem::instance = new HexusOpponentLightningGolem();
	}

	return HexusOpponentLightningGolem::instance;
}

HexusOpponentLightningGolem::HexusOpponentLightningGolem() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Caverns_Enemies_LightningGolem_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameCaverns,
	1.0f,
	Vec2(-32.0f, -128.0f),
	Vec2(-16.0f, -180.0f),
	HexusOpponentLightningGolem::OpponentSaveKey,
	HexusOpponentData::Difficulty::Stupid,
	Card::CardStyle::Shadow,
	HexusOpponentData::generateReward(0.495f),
	HexusOpponentData::generateDeck(25, 0.495f,
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

HexusOpponentLightningGolem::~HexusOpponentLightningGolem()
{
}
