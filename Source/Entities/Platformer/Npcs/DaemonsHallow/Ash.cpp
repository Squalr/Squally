#include "Ash.h"

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

const std::string Ash::MapKey = "ash";
HexusOpponentData* Ash::HexusOpponentDataInstance = nullptr;
const std::string Ash::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_ASH";

Ash* Ash::deserialize(ValueMap& properties)
{
	Ash* instance = new Ash(properties);

	instance->autorelease();

	return instance;
}

Ash::Ash(ValueMap& properties) : super(properties,
	Ash::MapKey,
	EntityResources::Npcs_DaemonsHallow_Ash_Animations,
	EntityResources::Npcs_DaemonsHallow_Ash_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Ash::getHexusOpponentData();
}

Ash::~Ash()
{
}

Vec2 Ash::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Ash::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_DaemonsHallow_Ash::create();
}

HexusOpponentData* Ash::getHexusOpponentData()
{
	if (Ash::HexusOpponentDataInstance == nullptr)
	{
		Ash::HexusOpponentDataInstance = new HexusOpponentData(
			nullptr,
			HexusResources::Menus_HexusFrameDaemonsHallow,
			Vec2(-32.0f, -112.0f),
			Ash::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Fire,
			HexusOpponentData::generateDeck(32, 0.652f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Steal),
				CardList::getInstance()->cardListByName.at(CardKeys::Absorb),
				CardList::getInstance()->cardListByName.at(CardKeys::Mov),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				CardList::getInstance()->cardListByName.at(CardKeys::Absorb),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),
			}),
			nullptr,
			nullptr
		);
	}

	return Ash::HexusOpponentDataInstance;
}