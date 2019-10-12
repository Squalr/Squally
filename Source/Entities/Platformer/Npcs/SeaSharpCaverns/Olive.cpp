#include "Olive.h"

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

#include "Strings/Platformer/Entities/Names/Npcs/SeaSharpCaverns/Olive.h"

using namespace cocos2d;

const std::string Olive::MapKeyOlive = "olive";
HexusOpponentData* Olive::HexusOpponentDataInstance = nullptr;
const std::string Olive::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_OLIVE";

Olive* Olive::deserialize(ValueMap& properties)
{
	Olive* instance = new Olive(properties);

	instance->autorelease();

	return instance;
}

Olive::Olive(ValueMap& properties) : super(properties,
	Olive::MapKeyOlive,
	EntityResources::Npcs_SeaSharpCaverns_Olive_Animations,
	EntityResources::Npcs_SeaSharpCaverns_Olive_Emblem,
	Size(112.0f, 160.0f),
	1.05f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Olive::getHexusOpponentData();
}

Olive::~Olive()
{
}

Vec2 Olive::getDialogueOffset()
{
	return Vec2(0.0f, -32.0f);
}

LocalizedString* Olive::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_SeaSharpCaverns_Olive::create();
}

HexusOpponentData* Olive::getHexusOpponentData()
{
	if (Olive::HexusOpponentDataInstance == nullptr)
	{
		Olive::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Npcs_SeaSharpCaverns_Olive_Animations,
			HexusResources::Menus_HexusFrameSeaSharpCaverns,
			1.05f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -112.0f),
			Olive::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Earth,
			0.339f,
			HexusOpponentData::generateDeck(32, 0.339f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Steal),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
				CardList::getInstance()->cardListByName.at(CardKeys::Flip2),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
			}),
			{ },
			nullptr
		);
	}

	return Olive::HexusOpponentDataInstance;
}