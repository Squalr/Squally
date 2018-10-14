#include "HexusOpponentSkeletalPriestess.h"

const std::string HexusOpponentSkeletalPriestess::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_SKELETAL_PRIESTESS";
HexusOpponentSkeletalPriestess* HexusOpponentSkeletalPriestess::instance = nullptr;

HexusOpponentSkeletalPriestess* HexusOpponentSkeletalPriestess::getInstance()
{
	if (HexusOpponentSkeletalPriestess::instance == nullptr)
	{
		HexusOpponentSkeletalPriestess::instance = new HexusOpponentSkeletalPriestess();
	}

	return HexusOpponentSkeletalPriestess::instance;
}

HexusOpponentSkeletalPriestess::HexusOpponentSkeletalPriestess() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Obelisk_Enemies_SkeletalPriestess_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameObelisk,
	0.85f,
	Vec2(-48.0f, -64.0f),
	Vec2(-16.0f, -48.0f),
	HexusOpponentSkeletalPriestess::OpponentSaveKey,
	HexusOpponentData::Difficulty::Stupid,
	Card::CardStyle::Earth,
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal4),
		CardList::getInstance()->cardListByName->at(CardKeys::LogicalAnd),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex4),
	},
	HexusOpponentData::generateDeck(25, 0, 12, 0.33f, 0.33f,
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

HexusOpponentSkeletalPriestess::~HexusOpponentSkeletalPriestess()
{
}
