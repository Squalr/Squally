#include "Toben.h"

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

const std::string Toben::MapKeyToben = "toben";
HexusOpponentData* Toben::HexusOpponentDataInstance = nullptr;
const std::string Toben::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_TOBEN";

Toben* Toben::deserialize(ValueMap& properties)
{
	Toben* instance = new Toben(properties);

	instance->autorelease();

	return instance;
}

Toben::Toben(ValueMap& properties) : super(properties,
	Toben::MapKeyToben,
	EntityResources::Npcs_EndianForest_Toben_Animations,
	EntityResources::Npcs_EndianForest_Toben_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Toben::getHexusOpponentData();
}

Toben::~Toben()
{
}

Vec2 Toben::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Toben::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_EndianForest_Toben::create();
}

HexusOpponentData* Toben::getHexusOpponentData()
{
	if (Toben::HexusOpponentDataInstance == nullptr)
	{
		Toben::HexusOpponentDataInstance = new HexusOpponentData(
			nullptr,
			HexusResources::Menus_HexusFrameEndianForest,
			Vec2(-32.0f, -112.0f),
			Toben::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Earth,
			HexusOpponentData::generateDeck(32, 0.009f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
				CardList::getInstance()->cardListByName.at(CardKeys::Flip1),
				CardList::getInstance()->cardListByName.at(CardKeys::Flip2),
				CardList::getInstance()->cardListByName.at(CardKeys::Mov),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
				CardList::getInstance()->cardListByName.at(CardKeys::ReturnToHand),
			}),
			nullptr,
			nullptr
		);
	}

	return Toben::HexusOpponentDataInstance;
}