#include "Magnus.h"

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

const std::string Magnus::MapKeyMagnus = "magnus";
HexusOpponentData* Magnus::HexusOpponentDataInstance = nullptr;
const std::string Magnus::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_MAGNUS";

Magnus* Magnus::deserialize(ValueMap& properties)
{
	Magnus* instance = new Magnus(properties);

	instance->autorelease();

	return instance;
}

Magnus::Magnus(ValueMap& properties) : super(properties,
	Magnus::MapKeyMagnus,
	EntityResources::Npcs_DaemonsHallow_Magnus_Animations,
	EntityResources::Npcs_DaemonsHallow_Magnus_Emblem,
	Size(112.0f, 160.0f),
	0.85f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Magnus::getHexusOpponentData();
}

Magnus::~Magnus()
{
}

Vec2 Magnus::getAvatarFrameOffset()
{
	return Vec2(-32.0f, -112.0f);
}

HexusOpponentData* Magnus::getHexusOpponentData()
{
	if (Magnus::HexusOpponentDataInstance == nullptr)
	{
		Magnus::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Npcs_DaemonsHallow_Magnus_Animations,
			HexusResources::Menus_HexusFrameDaemonsHallow,
			0.85f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -112.0f),
			Magnus::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Fire,
			0.714f,
			HexusOpponentData::generateDeck(32, 0.714f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Flip2),
				CardList::getInstance()->cardListByName.at(CardKeys::Kill),
				CardList::getInstance()->cardListByName.at(CardKeys::Mov),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				CardList::getInstance()->cardListByName.at(CardKeys::ReturnToHand),
				CardList::getInstance()->cardListByName.at(CardKeys::Kill),
				CardList::getInstance()->cardListByName.at(CardKeys::Mov),
				CardList::getInstance()->cardListByName.at(CardKeys::Flip3),

			}),
			nullptr
		);
	}

	return Magnus::HexusOpponentDataInstance;
}