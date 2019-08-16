#include "Cleopatra.h"

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

const std::string Cleopatra::MapKeyCleopatra = "cleopatra";
HexusOpponentData* Cleopatra::HexusOpponentDataInstance = nullptr;
const std::string Cleopatra::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_CLEOPATRA";

Cleopatra* Cleopatra::deserialize(ValueMap& properties)
{
	Cleopatra* instance = new Cleopatra(properties);

	instance->autorelease();

	return instance;
}

Cleopatra::Cleopatra(ValueMap& properties) : super(properties,
	Cleopatra::MapKeyCleopatra,
	EntityResources::Npcs_UnderflowRuins_Cleopatra_Animations,
	EntityResources::Npcs_UnderflowRuins_Cleopatra_Emblem,
	Size(112.0f, 160.0f),
	0.9f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Cleopatra::getHexusOpponentData();
}

Cleopatra::~Cleopatra()
{
}

Vec2 Cleopatra::getAvatarFrameOffset()
{
	return Vec2(-32.0f, -144.0f);
}

HexusOpponentData* Cleopatra::getHexusOpponentData()
{
	if (Cleopatra::HexusOpponentDataInstance == nullptr)
	{
		Cleopatra::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Npcs_UnderflowRuins_Cleopatra_Animations,
			HexusResources::Menus_HexusFrameUnderflowRuins,
			0.9f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -172.0f),
			Vec2(-32.0f, -144.0f),
			Cleopatra::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Light,
			0.250f,
			HexusOpponentData::generateDeck(32, 0.250f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
				CardList::getInstance()->cardListByName.at(CardKeys::Mov),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),

			}),
			nullptr
		);
	}

	return Cleopatra::HexusOpponentDataInstance;
}