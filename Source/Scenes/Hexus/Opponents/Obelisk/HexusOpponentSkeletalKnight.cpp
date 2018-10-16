#include "HexusOpponentSkeletalKnight.h"

const std::string HexusOpponentSkeletalKnight::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_SKELETAL_KNIGHT";
HexusOpponentSkeletalKnight* HexusOpponentSkeletalKnight::instance = nullptr;

HexusOpponentSkeletalKnight* HexusOpponentSkeletalKnight::getInstance()
{
	if (HexusOpponentSkeletalKnight::instance == nullptr)
	{
		HexusOpponentSkeletalKnight::instance = new HexusOpponentSkeletalKnight();
	}

	return HexusOpponentSkeletalKnight::instance;
}

HexusOpponentSkeletalKnight::HexusOpponentSkeletalKnight() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Obelisk_Enemies_SkeletalKnight_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameObelisk,
	0.85f,
	Vec2(-48.0f, -64.0f),
	Vec2(-32.0f, -32.0f),
	HexusOpponentSkeletalKnight::OpponentSaveKey,
	HexusOpponentData::Difficulty::Stupid,
	Card::CardStyle::Earth,
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal4),
		CardList::getInstance()->cardListByName->at(CardKeys::LogicalAnd),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex4),
	},
	HexusOpponentData::generateDeck(25, 0.8f,
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

HexusOpponentSkeletalKnight::~HexusOpponentSkeletalKnight()
{
}
