#include "HexusOpponentGoblinElf.h"

const std::string HexusOpponentGoblinElf::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_GOBLIN_ELF";
HexusOpponentGoblinElf* HexusOpponentGoblinElf::instance = nullptr;

HexusOpponentGoblinElf* HexusOpponentGoblinElf::getInstance()
{
	if (HexusOpponentGoblinElf::instance == nullptr)
	{
		HexusOpponentGoblinElf::instance = new HexusOpponentGoblinElf();
	}

	return HexusOpponentGoblinElf::instance;
}

HexusOpponentGoblinElf::HexusOpponentGoblinElf() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Snow_Enemies_GoblinElf_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameIceCaps,
	0.75f,
	Vec2(-48.0f, -64.0f),
	Vec2(-16.0f, -40.0f),
	HexusOpponentGoblinElf::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.63f),
	HexusOpponentData::generateDeck(25, 0.63f,
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

HexusOpponentGoblinElf::~HexusOpponentGoblinElf()
{
}
