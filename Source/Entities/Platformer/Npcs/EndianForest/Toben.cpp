#include "Toben.h"

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

const std::string Toben::MapKeyToben = "toben";
HexusOpponentData* Toben::HexusOpponentDataInstance = nullptr;
const std::string Toben::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_TOBEN";

Toben* Toben::deserialize(ValueMap& initProperties)
{
	Toben* instance = new Toben(initProperties);

	instance->autorelease();

	return instance;
}

Toben::Toben(ValueMap& initProperties) : NpcBase(initProperties,
	EntityResources::Npcs_EndianForest_Toben_Animations,
	EntityResources::Npcs_EndianForest_Toben_Emblem,
	Size(112.0f, 160.0f),
	1.05f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Toben::getHexusOpponentData();
}

Toben::~Toben()
{
}

Vec2 Toben::getAvatarFrameOffset()
{
	return Vec2(-32.0f, -112.0f);
}

HexusOpponentData* Toben::getHexusOpponentData()
{
	if (Toben::HexusOpponentDataInstance == nullptr)
	{
		Toben::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Npcs_EndianForest_Toben_Animations,
			HexusResources::Menus_HexusFrameEndianForest,
			1.05f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -112.0f),
			Toben::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Earth,
			0.009f,
			HexusOpponentData::generateDeck(32, 0.009f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
				CardList::getInstance()->cardListByName.at(CardKeys::Flip1),
				CardList::getInstance()->cardListByName.at(CardKeys::Flip2),
				CardList::getInstance()->cardListByName.at(CardKeys::Mov),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
				CardList::getInstance()->cardListByName.at(CardKeys::ReturnToHand),

			}),
			nullptr
		);
	}

	return Toben::HexusOpponentDataInstance;
}