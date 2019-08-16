#include "Thatcher.h"

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

const std::string Thatcher::MapKeyThatcher = "thatcher";
HexusOpponentData* Thatcher::HexusOpponentDataInstance = nullptr;
const std::string Thatcher::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_THATCHER";

Thatcher* Thatcher::deserialize(ValueMap& properties)
{
	Thatcher* instance = new Thatcher(properties);

	instance->autorelease();

	return instance;
}

Thatcher::Thatcher(ValueMap& properties) : super(properties,
	Thatcher::MapKeyThatcher,
	EntityResources::Npcs_BalmerPeaks_Thatcher_Animations,
	EntityResources::Npcs_BalmerPeaks_Thatcher_Emblem,
	Size(112.0f, 160.0f),
	0.9f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Thatcher::getHexusOpponentData();
}

Thatcher::~Thatcher()
{
}

Vec2 Thatcher::getAvatarFrameOffset()
{
	return Vec2(-32.0f, -112.0f);
}

HexusOpponentData* Thatcher::getHexusOpponentData()
{
	if (Thatcher::HexusOpponentDataInstance == nullptr)
	{
		Thatcher::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Npcs_BalmerPeaks_Thatcher_Animations,
			HexusResources::Menus_HexusFrameBalmerPeaks,
			0.9f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -112.0f),
			Thatcher::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Water,
			0.625f,
			HexusOpponentData::generateDeck(32, 0.625f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
				CardList::getInstance()->cardListByName.at(CardKeys::Steal),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				CardList::getInstance()->cardListByName.at(CardKeys::Absorb),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),

			}),
			nullptr
		);
	}

	return Thatcher::HexusOpponentDataInstance;
}