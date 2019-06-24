//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED. ONLY EDIT NON-GENERATED SECTIONS. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Olive.h"

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

const std::string Olive::MapKeyOlive = "olive";
HexusOpponentData* Olive::HexusOpponentDataInstance = nullptr;
const std::string Olive::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_OLIVE";

Olive* Olive::deserialize(ValueMap& initProperties)
{
	Olive* instance = new Olive(initProperties);

	instance->autorelease();

	return instance;
}

Olive::Olive(ValueMap& initProperties) : NpcBase(initProperties,
	EntityResources::Npcs_SeaSharpCaverns_Olive_Animations,
	EntityResources::Npcs_SeaSharpCaverns_Olive_Emblem,
	PlatformerCollisionType::FriendlyNpc,
	Size(112.0f, 160.0f),
	1.05f,
	Vec2(0.0f, 0.0f),
	16,
	8)
{
	this->hexusOpponentData = Olive::getHexusOpponentData();
}

Olive::~Olive()
{
}

Vec2 Olive::getAvatarFrameOffset()
{
	return Vec2(-32.0f, -112.0f);
}

HexusOpponentData* Olive::getHexusOpponentData()
{
	if (Olive::HexusOpponentDataInstance == nullptr)
	{
		Olive::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Npcs_SeaSharpCaverns_Olive_Animations,
			HexusResources::Menus_HexusFrameSeaSharpCaverns,
			1.05f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -112.0f),
			Olive::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Earth,
			0.339f,
			HexusOpponentData::generateDeck(32, 0.339f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Steal),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
				CardList::getInstance()->cardListByName.at(CardKeys::Flip2),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),

			}),
			nullptr
		);
	}

	return Olive::HexusOpponentDataInstance;
}