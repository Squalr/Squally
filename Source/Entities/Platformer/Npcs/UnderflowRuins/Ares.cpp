#include "Ares.h"

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

const std::string Ares::MapKeyAres = "ares";
HexusOpponentData* Ares::HexusOpponentDataInstance = nullptr;
const std::string Ares::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_ARES";

Ares* Ares::deserialize(ValueMap& properties)
{
	Ares* instance = new Ares(properties);

	instance->autorelease();

	return instance;
}

Ares::Ares(ValueMap& properties) : super(properties,
	Ares::MapKeyAres,
	EntityResources::Npcs_UnderflowRuins_Ares_Animations,
	EntityResources::Npcs_UnderflowRuins_Ares_Emblem,
	Size(112.0f, 160.0f),
	1.05f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Ares::getHexusOpponentData();
}

Ares::~Ares()
{
}

Vec2 Ares::getAvatarFrameOffset()
{
	return Vec2(-32.0f, -112.0f);
}

HexusOpponentData* Ares::getHexusOpponentData()
{
	if (Ares::HexusOpponentDataInstance == nullptr)
	{
		Ares::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Npcs_UnderflowRuins_Ares_Animations,
			HexusResources::Menus_HexusFrameUnderflowRuins,
			1.05f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -112.0f),
			Ares::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Light,
			0.161f,
			HexusOpponentData::generateDeck(32, 0.161f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
				CardList::getInstance()->cardListByName.at(CardKeys::Addition),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
				CardList::getInstance()->cardListByName.at(CardKeys::Addition),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),

			}),
			nullptr
		);
	}

	return Ares::HexusOpponentDataInstance;
}