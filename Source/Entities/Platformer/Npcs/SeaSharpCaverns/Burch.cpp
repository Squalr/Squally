#include "Burch.h"

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

const std::string Burch::MapKeyBurch = "burch";
HexusOpponentData* Burch::HexusOpponentDataInstance = nullptr;
const std::string Burch::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_BURCH";

Burch* Burch::deserialize(ValueMap& properties)
{
	Burch* instance = new Burch(properties);

	instance->autorelease();

	return instance;
}

Burch::Burch(ValueMap& properties) : super(properties,
	Burch::MapKeyBurch,
	EntityResources::Npcs_SeaSharpCaverns_Burch_Animations,
	EntityResources::Npcs_SeaSharpCaverns_Burch_Emblem,
	Size(112.0f, 160.0f),
	1.05f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Burch::getHexusOpponentData();
}

Burch::~Burch()
{
}

Vec2 Burch::getDialogueOffset()
{
	return Vec2(-32.0f, -112.0f);
}

LocalizedString* Burch::getEntityName()
{
	return nullptr;
}

HexusOpponentData* Burch::getHexusOpponentData()
{
	if (Burch::HexusOpponentDataInstance == nullptr)
	{
		Burch::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Npcs_SeaSharpCaverns_Burch_Animations,
			HexusResources::Menus_HexusFrameSeaSharpCaverns,
			1.05f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -112.0f),
			Burch::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Earth,
			0.277f,
			HexusOpponentData::generateDeck(32, 0.277f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
				CardList::getInstance()->cardListByName.at(CardKeys::Flip2),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Steal),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),

			}),
			nullptr
		);
	}

	return Burch::HexusOpponentDataInstance;
}