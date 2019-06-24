//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED. ONLY EDIT NON-GENERATED SECTIONS. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Blackbeard.h"

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

const std::string Blackbeard::MapKeyBlackbeard = "blackbeard";
HexusOpponentData* Blackbeard::HexusOpponentDataInstance = nullptr;
const std::string Blackbeard::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_BLACKBEARD";

Blackbeard* Blackbeard::deserialize(ValueMap& initProperties)
{
	Blackbeard* instance = new Blackbeard(initProperties);

	instance->autorelease();

	return instance;
}

Blackbeard::Blackbeard(ValueMap& initProperties) : NpcBase(initProperties,
	EntityResources::Npcs_EndianForest_Blackbeard_Animations,
	EntityResources::Npcs_EndianForest_Blackbeard_Emblem,
	PlatformerCollisionType::FriendlyNpc,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f),
	16,
	8)
{
	this->hexusOpponentData = Blackbeard::getHexusOpponentData();
}

Blackbeard::~Blackbeard()
{
}

Vec2 Blackbeard::getAvatarFrameOffset()
{
	return Vec2(-32.0f, -112.0f);
}

HexusOpponentData* Blackbeard::getHexusOpponentData()
{
	if (Blackbeard::HexusOpponentDataInstance == nullptr)
	{
		Blackbeard::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Npcs_EndianForest_Blackbeard_Animations,
			HexusResources::Menus_HexusFrameEndianForest,
			1.0f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -160.0f),
			Vec2(-32.0f, -112.0f),
			Blackbeard::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Earth,
			0.027f,
			HexusOpponentData::generateDeck(32, 0.027f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Flip1),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
				CardList::getInstance()->cardListByName.at(CardKeys::Flip2),
				CardList::getInstance()->cardListByName.at(CardKeys::Mov),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
				CardList::getInstance()->cardListByName.at(CardKeys::ReturnToHand),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),

			}),
			nullptr
		);
	}

	return Blackbeard::HexusOpponentDataInstance;
}