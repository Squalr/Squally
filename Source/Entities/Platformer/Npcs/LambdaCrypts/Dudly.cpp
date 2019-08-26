#include "Dudly.h"

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

#include "Strings/Platformer/Entities/Names/Npcs/LambdaCrypts/Dudly.h"

using namespace cocos2d;

const std::string Dudly::MapKeyDudly = "dudly";
HexusOpponentData* Dudly::HexusOpponentDataInstance = nullptr;
const std::string Dudly::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_DUDLY";

Dudly* Dudly::deserialize(ValueMap& properties)
{
	Dudly* instance = new Dudly(properties);

	instance->autorelease();

	return instance;
}

Dudly::Dudly(ValueMap& properties) : super(properties,
	Dudly::MapKeyDudly,
	EntityResources::Npcs_LambdaCrypts_Dudly_Animations,
	EntityResources::Npcs_LambdaCrypts_Dudly_Emblem,
	Size(112.0f, 160.0f),
	0.9f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Dudly::getHexusOpponentData();
}

Dudly::~Dudly()
{
}

Vec2 Dudly::getDialogueOffset()
{
	return Vec2(0.0f, -32.0f);
}

LocalizedString* Dudly::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_LambdaCrypts_Dudly::create();
}

HexusOpponentData* Dudly::getHexusOpponentData()
{
	if (Dudly::HexusOpponentDataInstance == nullptr)
	{
		Dudly::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Npcs_LambdaCrypts_Dudly_Animations,
			HexusResources::Menus_HexusFrameLambdaCrypts,
			0.9f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -112.0f),
			Dudly::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Shadow,
			0.777f,
			HexusOpponentData::generateDeck(32, 0.777f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::ReturnToHand),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
				CardList::getInstance()->cardListByName.at(CardKeys::Mov),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
				CardList::getInstance()->cardListByName.at(CardKeys::Subtraction),
				CardList::getInstance()->cardListByName.at(CardKeys::Inverse),
				CardList::getInstance()->cardListByName.at(CardKeys::Addition),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),

			}),
			nullptr
		);
	}

	return Dudly::HexusOpponentDataInstance;
}