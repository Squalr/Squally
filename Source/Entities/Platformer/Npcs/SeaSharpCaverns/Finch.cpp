#include "Finch.h"

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

#include "Strings/Platformer/Entities/Names/Npcs/SeaSharpCaverns/Finch.h"

using namespace cocos2d;

const std::string Finch::MapKeyFinch = "finch";
HexusOpponentData* Finch::HexusOpponentDataInstance = nullptr;
const std::string Finch::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_FINCH";

Finch* Finch::deserialize(ValueMap& properties)
{
	Finch* instance = new Finch(properties);

	instance->autorelease();

	return instance;
}

Finch::Finch(ValueMap& properties) : super(properties,
	Finch::MapKeyFinch,
	nullptr,
	EntityResources::Npcs_SeaSharpCaverns_Finch_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Finch::getHexusOpponentData();
}

Finch::~Finch()
{
}

Vec2 Finch::getDialogueOffset()
{
	return Vec2(0.0f, -32.0f);
}

LocalizedString* Finch::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_SeaSharpCaverns_Finch::create();
}

HexusOpponentData* Finch::getHexusOpponentData()
{
	if (Finch::HexusOpponentDataInstance == nullptr)
	{
		Finch::HexusOpponentDataInstance = new HexusOpponentData(
			nullptr,
			HexusResources::Menus_HexusFrameSeaSharpCaverns,
			Vec2(-32.0f, -112.0f),
			Finch::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Earth,
			HexusOpponentData::generateDeck(32, 0.295f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
				CardList::getInstance()->cardListByName.at(CardKeys::Steal),
				CardList::getInstance()->cardListByName.at(CardKeys::ReturnToHand),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
			}),
			nullptr,
			nullptr
		);
	}

	return Finch::HexusOpponentDataInstance;
}