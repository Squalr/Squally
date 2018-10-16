#include "HexusOpponentSkeletalWarrior.h"

const std::string HexusOpponentSkeletalWarrior::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_SKELETAL_WARRIOR";
HexusOpponentSkeletalWarrior* HexusOpponentSkeletalWarrior::instance = nullptr;

HexusOpponentSkeletalWarrior* HexusOpponentSkeletalWarrior::getInstance()
{
	if (HexusOpponentSkeletalWarrior::instance == nullptr)
	{
		HexusOpponentSkeletalWarrior::instance = new HexusOpponentSkeletalWarrior();
	}

	return HexusOpponentSkeletalWarrior::instance;
}

HexusOpponentSkeletalWarrior::HexusOpponentSkeletalWarrior() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Caverns_Enemies_SkeletalWarrior_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameCaverns,
	1.0f,
	Vec2(-32.0f, -48.0f),
	Vec2(-32.0f, -32.0f),
	HexusOpponentSkeletalWarrior::OpponentSaveKey,
	HexusOpponentData::Difficulty::Stupid,
	Card::CardStyle::Shadow,
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal3),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal2),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal1),
	},
	HexusOpponentData::generateDeck(25, 0.455f,
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

HexusOpponentSkeletalWarrior::~HexusOpponentSkeletalWarrior()
{
}
