#include "Leroy.h"

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

const std::string Leroy::MapKeyLeroy = "leroy";
HexusOpponentData* Leroy::HexusOpponentDataInstance = nullptr;
const std::string Leroy::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_LEROY";

Leroy* Leroy::deserialize(ValueMap& properties)
{
	Leroy* instance = new Leroy(properties);

	instance->autorelease();

	return instance;
}

Leroy::Leroy(ValueMap& properties) : super(properties,
	Leroy::MapKeyLeroy,
	EntityResources::Npcs_CastleValgrind_Leroy_Animations,
	EntityResources::Npcs_CastleValgrind_Leroy_Emblem,
	Size(112.0f, 160.0f),
	0.9f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Leroy::getHexusOpponentData();
}

Leroy::~Leroy()
{
}

Vec2 Leroy::getAvatarFrameOffset()
{
	return Vec2(-32.0f, -96.0f);
}

HexusOpponentData* Leroy::getHexusOpponentData()
{
	if (Leroy::HexusOpponentDataInstance == nullptr)
	{
		Leroy::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Npcs_CastleValgrind_Leroy_Animations,
			HexusResources::Menus_HexusFrameCastleValgrind,
			0.9f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -128.0f),
			Vec2(-32.0f, -96.0f),
			Leroy::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Air,
			0.420f,
			HexusOpponentData::generateDeck(32, 0.420f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				CardList::getInstance()->cardListByName.at(CardKeys::Steal),
				CardList::getInstance()->cardListByName.at(CardKeys::Mov),
				CardList::getInstance()->cardListByName.at(CardKeys::Addition),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),

			}),
			nullptr
		);
	}

	return Leroy::HexusOpponentDataInstance;
}