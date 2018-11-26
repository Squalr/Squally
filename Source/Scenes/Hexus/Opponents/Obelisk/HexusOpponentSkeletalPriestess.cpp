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
	EntityResources::Platformer_Environment_Obelisk_Enemies_SkeletalPriestess_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameObelisk,
	0.85f,
	Vec2(-48.0f, -64.0f),
	Vec2(-16.0f, -48.0f),
	HexusOpponentSkeletalPriestess::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.885f),
	HexusOpponentData::generateDeck(25, 0.885f,
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
