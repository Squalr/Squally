#include "Geryon.h"

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

#include "Strings/Platformer/Entities/Names/Npcs/UnderflowRuins/Geryon.h"

using namespace cocos2d;

const std::string Geryon::MapKeyGeryon = "geryon";
HexusOpponentData* Geryon::HexusOpponentDataInstance = nullptr;
const std::string Geryon::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_GERYON";

Geryon* Geryon::deserialize(ValueMap& properties)
{
	Geryon* instance = new Geryon(properties);

	instance->autorelease();

	return instance;
}

Geryon::Geryon(ValueMap& properties) : super(properties,
	Geryon::MapKeyGeryon,
	EntityResources::Npcs_UnderflowRuins_Geryon_Animations,
	EntityResources::Npcs_UnderflowRuins_Geryon_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Geryon::getHexusOpponentData();
}

Geryon::~Geryon()
{
}

Vec2 Geryon::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Geryon::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_UnderflowRuins_Geryon::create();
}

HexusOpponentData* Geryon::getHexusOpponentData()
{
	if (Geryon::HexusOpponentDataInstance == nullptr)
	{
		Geryon::HexusOpponentDataInstance = new HexusOpponentData(
			nullptr,
			HexusResources::Menus_HexusFrameUnderflowRuins,
			Vec2(-32.0f, -112.0f),
			Geryon::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Light,
			HexusOpponentData::generateDeck(32, 0.179f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Addition),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				CardList::getInstance()->cardListByName.at(CardKeys::Flip2),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
				CardList::getInstance()->cardListByName.at(CardKeys::Flip2),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
				CardList::getInstance()->cardListByName.at(CardKeys::Mov),
			}),
			nullptr,
			nullptr
		);
	}

	return Geryon::HexusOpponentDataInstance;
}