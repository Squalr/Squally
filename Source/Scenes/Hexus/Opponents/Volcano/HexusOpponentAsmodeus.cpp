#include "HexusOpponentAsmodeus.h"

const std::string HexusOpponentAsmodeus::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_ASMODEUS";
HexusOpponentAsmodeus* HexusOpponentAsmodeus::instance = nullptr;

HexusOpponentAsmodeus* HexusOpponentAsmodeus::getInstance()
{
	if (HexusOpponentAsmodeus::instance == nullptr)
	{
		HexusOpponentAsmodeus::instance = new HexusOpponentAsmodeus();
	}

	return HexusOpponentAsmodeus::instance;
}

HexusOpponentAsmodeus::HexusOpponentAsmodeus() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Volcano_Enemies_Asmodeus_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameVolcano,
	0.85f,
	Vec2(-48.0f, -24.0f),
	Vec2(-32.0f, -48.0f),
	HexusOpponentAsmodeus::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.82f),
	HexusOpponentData::generateDeck(25, 0.82f,
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

HexusOpponentAsmodeus::~HexusOpponentAsmodeus()
{
}
