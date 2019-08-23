#include "PrincessPepper.h"

#include "cocos/math/CCGeometry.h"

#include "Scenes/Hexus/Card.h"
#include "Scenes/Hexus/CardData/CardData.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"
#include "Scenes/Hexus/StateOverride.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/EntityResources.h"
#include "Resources/HexusResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string PrincessPepper::MapKeyPrincessPepper = "princess-pepper";
HexusOpponentData* PrincessPepper::HexusOpponentDataInstance = nullptr;
const std::string PrincessPepper::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_PRINCESS_PEPPER";

PrincessPepper* PrincessPepper::deserialize(ValueMap& properties)
{
	PrincessPepper* instance = new PrincessPepper(properties);

	instance->autorelease();

	return instance;
}

PrincessPepper::PrincessPepper(ValueMap& properties) : super(properties,
	PrincessPepper::MapKeyPrincessPepper,
	EntityResources::Npcs_BalmerPeaks_PrincessPepper_Animations,
	EntityResources::Npcs_BalmerPeaks_PrincessPepper_Emblem,
	Size(112.0f, 160.0f),
	0.85f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = PrincessPepper::getHexusOpponentData();
}

PrincessPepper::~PrincessPepper()
{
}

Vec2 PrincessPepper::getDialogueOffset()
{
	return Vec2(-32.0f, -112.0f);
}

LocalizedString* PrincessPepper::getEntityName()
{
	return nullptr;
}

HexusOpponentData* PrincessPepper::getHexusOpponentData()
{
	if (PrincessPepper::HexusOpponentDataInstance == nullptr)
	{
		PrincessPepper::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Npcs_BalmerPeaks_PrincessPepper_Animations,
			HexusResources::Menus_HexusFrameBalmerPeaks,
			0.85f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -112.0f),
			PrincessPepper::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Water,
			0.598f,
			HexusOpponentData::generateDeck(32, 0.598f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				CardList::getInstance()->cardListByName.at(CardKeys::Kill),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),
				CardList::getInstance()->cardListByName.at(CardKeys::Absorb),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
				CardList::getInstance()->cardListByName.at(CardKeys::BonusMoves),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
				CardList::getInstance()->cardListByName.at(CardKeys::Flip3),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),

			}),
			nullptr
		);
	}

	return PrincessPepper::HexusOpponentDataInstance;
}