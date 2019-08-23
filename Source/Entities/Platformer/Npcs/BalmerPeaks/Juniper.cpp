#include "Juniper.h"

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

const std::string Juniper::MapKeyJuniper = "juniper";
HexusOpponentData* Juniper::HexusOpponentDataInstance = nullptr;
const std::string Juniper::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_JUNIPER";

Juniper* Juniper::deserialize(ValueMap& properties)
{
	Juniper* instance = new Juniper(properties);

	instance->autorelease();

	return instance;
}

Juniper::Juniper(ValueMap& properties) : super(properties,
	Juniper::MapKeyJuniper,
	EntityResources::Npcs_BalmerPeaks_Juniper_Animations,
	EntityResources::Npcs_BalmerPeaks_Juniper_Emblem,
	Size(112.0f, 160.0f),
	0.85f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Juniper::getHexusOpponentData();
}

Juniper::~Juniper()
{
}

Vec2 Juniper::getDialogueOffset()
{
	return Vec2(-32.0f, -112.0f);
}

LocalizedString* Juniper::getEntityName()
{
	return nullptr;
}

HexusOpponentData* Juniper::getHexusOpponentData()
{
	if (Juniper::HexusOpponentDataInstance == nullptr)
	{
		Juniper::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Npcs_BalmerPeaks_Juniper_Animations,
			HexusResources::Menus_HexusFrameBalmerPeaks,
			0.85f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -112.0f),
			Juniper::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Water,
			0.571f,
			HexusOpponentData::generateDeck(32, 0.571f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				CardList::getInstance()->cardListByName.at(CardKeys::Steal),
				CardList::getInstance()->cardListByName.at(CardKeys::Addition),
				CardList::getInstance()->cardListByName.at(CardKeys::Steal),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),

			}),
			nullptr
		);
	}

	return Juniper::HexusOpponentDataInstance;
}