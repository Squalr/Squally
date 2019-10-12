#include "Leon.h"

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

#include "Strings/Platformer/Entities/Names/Npcs/VoidStar/Leon.h"

using namespace cocos2d;

const std::string Leon::MapKeyLeon = "leon";
HexusOpponentData* Leon::HexusOpponentDataInstance = nullptr;
const std::string Leon::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_LEON";

Leon* Leon::deserialize(ValueMap& properties)
{
	Leon* instance = new Leon(properties);

	instance->autorelease();

	return instance;
}

Leon::Leon(ValueMap& properties) : super(properties,
	Leon::MapKeyLeon,
	EntityResources::Npcs_VoidStar_Leon_Animations,
	EntityResources::Npcs_VoidStar_Leon_Emblem,
	Size(112.0f, 160.0f),
	0.85f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Leon::getHexusOpponentData();
}

Leon::~Leon()
{
}

Vec2 Leon::getDialogueOffset()
{
	return Vec2(0.0f, -32.0f);
}

LocalizedString* Leon::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_VoidStar_Leon::create();
}

HexusOpponentData* Leon::getHexusOpponentData()
{
	if (Leon::HexusOpponentDataInstance == nullptr)
	{
		Leon::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Npcs_VoidStar_Leon_Animations,
			HexusResources::Menus_HexusFrameVoidStar,
			0.85f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -112.0f),
			Leon::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Shadow,
			0.971f,
			HexusOpponentData::generateDeck(32, 0.971f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),
				CardList::getInstance()->cardListByName.at(CardKeys::Kill),
				CardList::getInstance()->cardListByName.at(CardKeys::Flip4),
				CardList::getInstance()->cardListByName.at(CardKeys::Flip3),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
			}),
			{ },
			nullptr
		);
	}

	return Leon::HexusOpponentDataInstance;
}