#include "Mabel.h"

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

#include "Strings/Platformer/Entities/Names/Npcs/CastleValgrind/Mabel.h"

using namespace cocos2d;

const std::string Mabel::MapKeyMabel = "mabel";
HexusOpponentData* Mabel::HexusOpponentDataInstance = nullptr;
const std::string Mabel::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_MABEL";

Mabel* Mabel::deserialize(ValueMap& properties)
{
	Mabel* instance = new Mabel(properties);

	instance->autorelease();

	return instance;
}

Mabel::Mabel(ValueMap& properties) : super(properties,
	Mabel::MapKeyMabel,
	EntityResources::Npcs_CastleValgrind_Mabel_Animations,
	EntityResources::Npcs_CastleValgrind_Mabel_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Mabel::getHexusOpponentData();
}

Mabel::~Mabel()
{
}

Vec2 Mabel::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Mabel::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_CastleValgrind_Mabel::create();
}

HexusOpponentData* Mabel::getHexusOpponentData()
{
	if (Mabel::HexusOpponentDataInstance == nullptr)
	{
		Mabel::HexusOpponentDataInstance = new HexusOpponentData(
			nullptr,
			HexusResources::Menus_HexusFrameCastleValgrind,
			Vec2(-32.0f, -112.0f),
			Mabel::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Air,
			HexusOpponentData::generateDeck(32, 0.429f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Steal),
				CardList::getInstance()->cardListByName.at(CardKeys::Steal),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
				CardList::getInstance()->cardListByName.at(CardKeys::Mov),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
			}),
			nullptr,
			nullptr
		);
	}

	return Mabel::HexusOpponentDataInstance;
}