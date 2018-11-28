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
	EntityResources::Environment_Volcano_Enemies_DemonWarrior_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameVolcano,
	0.85f,
	Vec2(-48.0f, -48.0f),
	Vec2(-16.0f, -64.0f),
	HexusOpponentDemonWarrior::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.775f),
	HexusOpponentData::generateDeck(25, 0.775f,
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
