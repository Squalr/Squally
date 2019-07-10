#include "Cindra.h"

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

const std::string Cindra::MapKeyCindra = "cindra";
HexusOpponentData* Cindra::HexusOpponentDataInstance = nullptr;
const std::string Cindra::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_CINDRA";

Cindra* Cindra::deserialize(ValueMap& initProperties)
{
	Cindra* instance = new Cindra(initProperties);

	instance->autorelease();

	return instance;
}

Cindra::Cindra(ValueMap& initProperties) : NpcBase(initProperties,
	EntityResources::Npcs_DaemonsHallow_Cindra_Animations,
	EntityResources::Npcs_DaemonsHallow_Cindra_Emblem,
	PlatformerCollisionType::FriendlyNpc,
	Size(112.0f, 160.0f),
	0.85f,
	Vec2(0.0f, 0.0f),
	16,
	8)
{
	this->hexusOpponentData = Cindra::getHexusOpponentData();
}

Cindra::~Cindra()
{
}

Vec2 Cindra::getAvatarFrameOffset()
{
	return Vec2(-32.0f, -112.0f);
}

HexusOpponentData* Cindra::getHexusOpponentData()
{
	if (Cindra::HexusOpponentDataInstance == nullptr)
	{
		Cindra::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Npcs_DaemonsHallow_Cindra_Animations,
			HexusResources::Menus_HexusFrameDaemonsHallow,
			0.85f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -112.0f),
			Cindra::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Fire,
			0.679f,
			HexusOpponentData::generateDeck(32, 0.679f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::ReturnToHand),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
				CardList::getInstance()->cardListByName.at(CardKeys::Steal),
				CardList::getInstance()->cardListByName.at(CardKeys::Kill),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Mov),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),

			}),
			nullptr
		);
	}

	return Cindra::HexusOpponentDataInstance;
}