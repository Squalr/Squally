#include "HexusOpponentEvilEye.h"

const std::string HexusOpponentEvilEye::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_EVIL_EYE";
HexusOpponentEvilEye* HexusOpponentEvilEye::instance = nullptr;

HexusOpponentEvilEye* HexusOpponentEvilEye::getInstance()
{
	if (HexusOpponentEvilEye::instance == nullptr)
	{
		HexusOpponentEvilEye::instance = new HexusOpponentEvilEye();
	}

	return HexusOpponentEvilEye::instance;
}

HexusOpponentEvilEye::HexusOpponentEvilEye() : HexusOpponentData(
	EntityResources::Platformer_Environment_Mech_Enemies_EvilEye_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameMech,
	0.7f,
	Vec2(-48.0f, -112.0f),
	Vec2(-16.0f, -180.0f),
	HexusOpponentEvilEye::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(1.0f),
	HexusOpponentData::generateDeck(25, 1.0f,
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

HexusOpponentEvilEye::~HexusOpponentEvilEye()
{
}
