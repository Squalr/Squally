//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED. ONLY EDIT NON-GENERATED SECTIONS. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Bodom.h"

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

const std::string Bodom::MapKeyBodom = "bodom";
HexusOpponentData* Bodom::HexusOpponentDataInstance = nullptr;
const std::string Bodom::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_BODOM";

Bodom* Bodom::deserialize(ValueMap& initProperties)
{
	Bodom* instance = new Bodom(initProperties);

	instance->autorelease();

	return instance;
}

Bodom::Bodom(ValueMap& initProperties) : NpcBase(initProperties,
	EntityResources::Npcs_BalmerPeaks_Bodom_Animations,
	EntityResources::Npcs_BalmerPeaks_Bodom_Emblem,
	PlatformerCollisionType::FriendlyNpc,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f),
	16,
	8)
{
	this->hexusOpponentData = Bodom::getHexusOpponentData();
}

Bodom::~Bodom()
{
}

Vec2 Bodom::getAvatarFrameOffset()
{
	return Vec2(-32.0f, -112.0f);
}

HexusOpponentData* Bodom::getHexusOpponentData()
{
	if (Bodom::HexusOpponentDataInstance == nullptr)
	{
		Bodom::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Npcs_BalmerPeaks_Bodom_Animations,
			HexusResources::Menus_HexusFrameBalmerPeaks,
			1.0f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -112.0f),
			Bodom::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Water,
			0.536f,
			HexusOpponentData::generateDeck(32, 0.536f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				CardList::getInstance()->cardListByName.at(CardKeys::Absorb),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
				CardList::getInstance()->cardListByName.at(CardKeys::Kill),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),

			}),
			nullptr
		);
	}

	return Bodom::HexusOpponentDataInstance;
}