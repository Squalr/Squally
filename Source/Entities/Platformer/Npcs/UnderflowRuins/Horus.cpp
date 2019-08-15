#include "Horus.h"

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

const std::string Horus::MapKeyHorus = "horus";
HexusOpponentData* Horus::HexusOpponentDataInstance = nullptr;
const std::string Horus::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_HORUS";

Horus* Horus::deserialize(ValueMap& initProperties)
{
	Horus* instance = new Horus(initProperties);

	instance->autorelease();

	return instance;
}

Horus::Horus(ValueMap& initProperties) : super(initProperties,
	Horus::MapKeyHorus,
	EntityResources::Npcs_UnderflowRuins_Horus_Animations,
	EntityResources::Npcs_UnderflowRuins_Horus_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Horus::getHexusOpponentData();
}

Horus::~Horus()
{
}

Vec2 Horus::getAvatarFrameOffset()
{
	return Vec2(-32.0f, -128.0f);
}

HexusOpponentData* Horus::getHexusOpponentData()
{
	if (Horus::HexusOpponentDataInstance == nullptr)
	{
		Horus::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Npcs_UnderflowRuins_Horus_Animations,
			HexusResources::Menus_HexusFrameUnderflowRuins,
			1.0f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -160.0f),
			Vec2(-32.0f, -128.0f),
			Horus::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Light,
			0.214f,
			HexusOpponentData::generateDeck(32, 0.214f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),
				CardList::getInstance()->cardListByName.at(CardKeys::Mov),

			}),
			nullptr
		);
	}

	return Horus::HexusOpponentDataInstance;
}