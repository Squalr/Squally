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

#include "Strings/Strings.h"

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

Vec2 Ares::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Ares::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_UnderflowRuins_Ares::create();
}

HexusOpponentData* Ares::getHexusOpponentData()
{
	if (Ares::HexusOpponentDataInstance == nullptr)
	{
		Ares::HexusOpponentDataInstance = new HexusOpponentData(
			nullptr,
			HexusResources::Menus_HexusFrameUnderflowRuins,
			Vec2(-32.0f, -112.0f),
			Ares::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Light,
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
			nullptr,
			nullptr
		);
	}

	return Ares::HexusOpponentDataInstance;
}