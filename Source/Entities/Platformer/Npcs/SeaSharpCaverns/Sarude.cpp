#include "Sarude.h"

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

#include "Strings/Platformer/Entities/Names/Npcs/SeaSharpCaverns/Sarude.h"

using namespace cocos2d;

const std::string Sarude::MapKeySarude = "sarude";
HexusOpponentData* Sarude::HexusOpponentDataInstance = nullptr;
const std::string Sarude::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_SARUDE";

Sarude* Sarude::deserialize(ValueMap& properties)
{
	Sarude* instance = new Sarude(properties);

	instance->autorelease();

	return instance;
}

Sarude::Sarude(ValueMap& properties) : super(properties,
	Sarude::MapKeySarude,
	EntityResources::Npcs_SeaSharpCaverns_Sarude_Animations,
	EntityResources::Npcs_SeaSharpCaverns_Sarude_Emblem,
	Size(112.0f, 160.0f),
	1.05f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Sarude::getHexusOpponentData();
}

Sarude::~Sarude()
{
}

Vec2 Sarude::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Sarude::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_SeaSharpCaverns_Sarude::create();
}

HexusOpponentData* Sarude::getHexusOpponentData()
{
	if (Sarude::HexusOpponentDataInstance == nullptr)
	{
		Sarude::HexusOpponentDataInstance = new HexusOpponentData(
			nullptr,
			HexusResources::Menus_HexusFrameSeaSharpCaverns,
			Vec2(-32.0f, -112.0f),
			Sarude::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Earth,
			HexusOpponentData::generateDeck(32, 0.366f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Flip2),
				CardList::getInstance()->cardListByName.at(CardKeys::Flip1),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				CardList::getInstance()->cardListByName.at(CardKeys::Addition),
			}),
			{
				
			},
			nullptr
		);
	}

	return Sarude::HexusOpponentDataInstance;
}