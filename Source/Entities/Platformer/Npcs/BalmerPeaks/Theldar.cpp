#include "Theldar.h"

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

#include "Strings/Platformer/Entities/Names/Npcs/BalmerPeaks/Theldar.h"

using namespace cocos2d;

const std::string Theldar::MapKeyTheldar = "theldar";
HexusOpponentData* Theldar::HexusOpponentDataInstance = nullptr;
const std::string Theldar::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_THELDAR";

Theldar* Theldar::deserialize(ValueMap& properties)
{
	Theldar* instance = new Theldar(properties);

	instance->autorelease();

	return instance;
}

Theldar::Theldar(ValueMap& properties) : super(properties,
	Theldar::MapKeyTheldar,
	EntityResources::Npcs_BalmerPeaks_Theldar_Animations,
	EntityResources::Npcs_BalmerPeaks_Theldar_Emblem,
	Size(112.0f, 160.0f),
	0.9f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Theldar::getHexusOpponentData();
}

Theldar::~Theldar()
{
}

Vec2 Theldar::getDialogueOffset()
{
	return Vec2(0.0f, -32.0f);
}

LocalizedString* Theldar::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_BalmerPeaks_Theldar::create();
}

HexusOpponentData* Theldar::getHexusOpponentData()
{
	if (Theldar::HexusOpponentDataInstance == nullptr)
	{
		Theldar::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Npcs_BalmerPeaks_Theldar_Animations,
			HexusResources::Menus_HexusFrameBalmerPeaks,
			0.9f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -112.0f),
			Theldar::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Water,
			0.607f,
			HexusOpponentData::generateDeck(32, 0.607f,
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
			{ },
			nullptr
		);
	}

	return Theldar::HexusOpponentDataInstance;
}