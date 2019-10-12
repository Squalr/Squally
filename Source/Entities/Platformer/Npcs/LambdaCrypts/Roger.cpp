#include "Roger.h"

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

#include "Strings/Platformer/Entities/Names/Npcs/LambdaCrypts/Roger.h"

using namespace cocos2d;

const std::string Roger::MapKeyRoger = "roger";
HexusOpponentData* Roger::HexusOpponentDataInstance = nullptr;
const std::string Roger::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_ROGER";

Roger* Roger::deserialize(ValueMap& properties)
{
	Roger* instance = new Roger(properties);

	instance->autorelease();

	return instance;
}

Roger::Roger(ValueMap& properties) : super(properties,
	Roger::MapKeyRoger,
	EntityResources::Npcs_LambdaCrypts_Roger_Animations,
	EntityResources::Npcs_LambdaCrypts_Roger_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Roger::getHexusOpponentData();
}

Roger::~Roger()
{
}

Vec2 Roger::getDialogueOffset()
{
	return Vec2(0.0f, -32.0f);
}

LocalizedString* Roger::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_LambdaCrypts_Roger::create();
}

HexusOpponentData* Roger::getHexusOpponentData()
{
	if (Roger::HexusOpponentDataInstance == nullptr)
	{
		Roger::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Npcs_LambdaCrypts_Roger_Animations,
			HexusResources::Menus_HexusFrameLambdaCrypts,
			1.0f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -112.0f),
			Roger::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Shadow,
			0.821f,
			HexusOpponentData::generateDeck(32, 0.821f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
				CardList::getInstance()->cardListByName.at(CardKeys::Kill),
				CardList::getInstance()->cardListByName.at(CardKeys::SuddenDeath),
				CardList::getInstance()->cardListByName.at(CardKeys::Steal),
			}),
			{ },
			nullptr
		);
	}

	return Roger::HexusOpponentDataInstance;
}