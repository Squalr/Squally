#include "HexusOpponentDemonWarrior.h"

const std::string HexusOpponentDemonWarrior::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_DEMON_WARRIOR";
HexusOpponentDemonWarrior* HexusOpponentDemonWarrior::instance = nullptr;

HexusOpponentDemonWarrior* HexusOpponentDemonWarrior::getInstance()
{
	if (HexusOpponentDemonWarrior::instance == nullptr)
	{
		HexusOpponentDemonWarrior::instance = new HexusOpponentDemonWarrior();
	}

	return HexusOpponentDemonWarrior::instance;
}

HexusOpponentDemonWarrior::HexusOpponentDemonWarrior() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Volcano_Enemies_DemonWarrior_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameVolcano,
	0.85f,
	Vec2(-48.0f, -48.0f),
	Vec2(-16.0f, -64.0f),
	HexusOpponentDemonWarrior::OpponentSaveKey,
	HexusOpponentData::Difficulty::Stupid,
	Card::CardStyle::Earth,
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal4),
		CardList::getInstance()->cardListByName->at(CardKeys::LogicalAnd),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex4),
	},
	HexusOpponentData::generateDeck(25, 0, 11, 0.33f, 0.33f,
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

HexusOpponentDemonWarrior::~HexusOpponentDemonWarrior()
{
}
