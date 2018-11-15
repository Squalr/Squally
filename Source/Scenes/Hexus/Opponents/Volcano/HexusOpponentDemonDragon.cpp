#include "HexusOpponentDemonDragon.h"

const std::string HexusOpponentDemonDragon::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_DEMON_DRAGON";
HexusOpponentDemonDragon* HexusOpponentDemonDragon::instance = nullptr;

HexusOpponentDemonDragon* HexusOpponentDemonDragon::getInstance()
{
	if (HexusOpponentDemonDragon::instance == nullptr)
	{
		HexusOpponentDemonDragon::instance = new HexusOpponentDemonDragon();
	}

	return HexusOpponentDemonDragon::instance;
}

HexusOpponentDemonDragon::HexusOpponentDemonDragon() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Volcano_Enemies_DemonDragon_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameVolcano,
	1.0f,
	Vec2(-48.0f, -64.0f),
	Vec2(-96.0f, -56.0f),
	HexusOpponentDemonDragon::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.755f),
	HexusOpponentData::generateDeck(25, 0.755f,
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

HexusOpponentDemonDragon::~HexusOpponentDemonDragon()
{
}
