#include "Rupert.h"

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

const std::string Rupert::MapKey = "rupert";
HexusOpponentData* Rupert::HexusOpponentDataInstance = nullptr;
const std::string Rupert::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_RUPERT";

Rupert* Rupert::deserialize(ValueMap& properties)
{
	Rupert* instance = new Rupert(properties);

	instance->autorelease();

	return instance;
}

Rupert::Rupert(ValueMap& properties) : super(properties,
	Rupert::MapKey,
	EntityResources::Npcs_DaemonsHallow_Rupert_Animations,
	EntityResources::Npcs_DaemonsHallow_Rupert_Emblem,
	Size(112.0f, 160.0f),
	1.05f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Rupert::getHexusOpponentData();
}

Rupert::~Rupert()
{
}

Vec2 Rupert::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Rupert::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_DaemonsHallow_Rupert::create();
}

HexusOpponentData* Rupert::getHexusOpponentData()
{
	if (Rupert::HexusOpponentDataInstance == nullptr)
	{
		Rupert::HexusOpponentDataInstance = new HexusOpponentData(
			nullptr,
			HexusResources::Menus_HexusFrameDaemonsHallow,
			Vec2(-32.0f, -112.0f),
			Rupert::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Fire,
			HexusOpponentData::generateDeck(32, 0.634f,
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

	return Rupert::HexusOpponentDataInstance;
}