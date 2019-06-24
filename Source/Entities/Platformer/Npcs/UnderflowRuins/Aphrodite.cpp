//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED. ONLY EDIT NON-GENERATED SECTIONS. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Aphrodite.h"

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

const std::string Aphrodite::MapKeyAphrodite = "aphrodite";
HexusOpponentData* Aphrodite::HexusOpponentDataInstance = nullptr;
const std::string Aphrodite::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_APHRODITE";

Aphrodite* Aphrodite::deserialize(ValueMap& initProperties)
{
	Aphrodite* instance = new Aphrodite(initProperties);

	instance->autorelease();

	return instance;
}

Aphrodite::Aphrodite(ValueMap& initProperties) : NpcBase(initProperties,
	EntityResources::Npcs_UnderflowRuins_Aphrodite_Animations,
	EntityResources::Npcs_UnderflowRuins_Aphrodite_Emblem,
	PlatformerCollisionType::FriendlyNpc,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f),
	16,
	8)
{
	this->hexusOpponentData = Aphrodite::getHexusOpponentData();
}

Aphrodite::~Aphrodite()
{
}

Vec2 Aphrodite::getAvatarFrameOffset()
{
	return Vec2(-32.0f, -112.0f);
}

HexusOpponentData* Aphrodite::getHexusOpponentData()
{
	if (Aphrodite::HexusOpponentDataInstance == nullptr)
	{
		Aphrodite::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Npcs_UnderflowRuins_Aphrodite_Animations,
			HexusResources::Menus_HexusFrameUnderflowRuins,
			1.0f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -112.0f),
			Aphrodite::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Light,
			0.134f,
			HexusOpponentData::generateDeck(32, 0.134f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
				CardList::getInstance()->cardListByName.at(CardKeys::Flip2),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				CardList::getInstance()->cardListByName.at(CardKeys::Mov),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),
				CardList::getInstance()->cardListByName.at(CardKeys::Mov),

			}),
			nullptr
		);
	}

	return Aphrodite::HexusOpponentDataInstance;
}