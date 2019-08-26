#include "Garin.h"

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

#include "Strings/Platformer/Entities/Names/Npcs/CastleValgrind/Garin.h"

using namespace cocos2d;

const std::string Garin::MapKeyGarin = "garin";
HexusOpponentData* Garin::HexusOpponentDataInstance = nullptr;
const std::string Garin::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_GARIN";

Garin* Garin::deserialize(ValueMap& properties)
{
	Garin* instance = new Garin(properties);

	instance->autorelease();

	return instance;
}

Garin::Garin(ValueMap& properties) : super(properties,
	Garin::MapKeyGarin,
	EntityResources::Npcs_CastleValgrind_Garin_Animations,
	EntityResources::Npcs_CastleValgrind_Garin_Emblem,
	Size(112.0f, 160.0f),
	0.85f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Garin::getHexusOpponentData();
}

Garin::~Garin()
{
}

Vec2 Garin::getDialogueOffset()
{
	return Vec2(0.0f, -32.0f);
}

LocalizedString* Garin::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_CastleValgrind_Garin::create();
}

HexusOpponentData* Garin::getHexusOpponentData()
{
	if (Garin::HexusOpponentDataInstance == nullptr)
	{
		Garin::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Npcs_CastleValgrind_Garin_Animations,
			HexusResources::Menus_HexusFrameCastleValgrind,
			0.85f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -112.0f),
			Garin::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Air,
			0.393f,
			HexusOpponentData::generateDeck(32, 0.393f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Steal),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				CardList::getInstance()->cardListByName.at(CardKeys::ReturnToHand),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),

			}),
			nullptr
		);
	}

	return Garin::HexusOpponentDataInstance;
}