#include "Brine.h"

#include "cocos/math/CCGeometry.h"

#include "Scenes/Hexus/Card.h"
#include "Scenes/Hexus/CardData/CardData.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"
#include "Scenes/Hexus/StateOverride.h"

#include "Resources/EntityResources.h"
#include "Resources/HexusResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Brine::MapKey = "brine";
HexusOpponentData* Brine::HexusOpponentDataInstance = nullptr;
const std::string Brine::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_BRINE";

Brine* Brine::deserialize(ValueMap& properties)
{
	Brine* instance = new Brine(properties);

	instance->autorelease();

	return instance;
}

Brine::Brine(ValueMap& properties) : super(properties,
	Brine::MapKey,
	EntityResources::Npcs_DaemonsHallow_Brine_Animations,
	EntityResources::Npcs_DaemonsHallow_Brine_Emblem,
	Size(112.0f, 160.0f),
	1.05f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Brine::getHexusOpponentData();
}

Brine::~Brine()
{
}

Vec2 Brine::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Brine::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_DaemonsHallow_Brine::create();
}

HexusOpponentData* Brine::getHexusOpponentData()
{
	if (Brine::HexusOpponentDataInstance == nullptr)
	{
		Brine::HexusOpponentDataInstance = new HexusOpponentData(
			nullptr,
			HexusResources::Menus_HexusFrameDaemonsHallow,
			Vec2(-32.0f, -112.0f),
			Brine::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Fire,
			HexusOpponentData::generateDeck(32, 0.661f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Flip2),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				CardList::getInstance()->cardListByName.at(CardKeys::Absorb),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Mov),
			}),
			nullptr,
			nullptr
		);
	}

	return Brine::HexusOpponentDataInstance;
}