#include "Brock.h"

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

const std::string Brock::MapKeyBrock = "brock";
HexusOpponentData* Brock::HexusOpponentDataInstance = nullptr;
const std::string Brock::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_BROCK";

Brock* Brock::deserialize(ValueMap& properties)
{
	Brock* instance = new Brock(properties);

	instance->autorelease();

	return instance;
}

Brock::Brock(ValueMap& properties) : super(properties,
	Brock::MapKeyBrock,
	EntityResources::Npcs_SeaSharpCaverns_Brock_Animations,
	EntityResources::Npcs_SeaSharpCaverns_Brock_Emblem,
	Size(112.0f, 160.0f),
	1.05f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Brock::getHexusOpponentData();
}

Brock::~Brock()
{
}

Vec2 Brock::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Brock::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_SeaSharpCaverns_Brock::create();
}

HexusOpponentData* Brock::getHexusOpponentData()
{
	if (Brock::HexusOpponentDataInstance == nullptr)
	{
		Brock::HexusOpponentDataInstance = new HexusOpponentData(
			nullptr,
			HexusResources::Menus_HexusFrameSeaSharpCaverns,
			Vec2(-32.0f, -112.0f),
			Brock::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Earth,
			HexusOpponentData::generateDeck(32, 0.268f,
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
			nullptr,
			nullptr
		);
	}

	return Brock::HexusOpponentDataInstance;
}