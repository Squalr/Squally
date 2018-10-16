#include "HexusOpponentSkeletalCleaver.h"

const std::string HexusOpponentSkeletalCleaver::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_SKELETAL_CLEAVER";
HexusOpponentSkeletalCleaver* HexusOpponentSkeletalCleaver::instance = nullptr;

HexusOpponentSkeletalCleaver* HexusOpponentSkeletalCleaver::getInstance()
{
	if (HexusOpponentSkeletalCleaver::instance == nullptr)
	{
		HexusOpponentSkeletalCleaver::instance = new HexusOpponentSkeletalCleaver();
	}

	return HexusOpponentSkeletalCleaver::instance;
}

HexusOpponentSkeletalCleaver::HexusOpponentSkeletalCleaver() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Obelisk_Enemies_SkeletalCleaver_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameObelisk,
	0.85f,
	Vec2(-48.0f, -64.0f),
	Vec2(-16.0f, -40.0f),
	HexusOpponentSkeletalCleaver::OpponentSaveKey,
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

HexusOpponentSkeletalCleaver::~HexusOpponentSkeletalCleaver()
{
}
