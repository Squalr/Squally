#include "Scaldor.h"

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

const std::string Scaldor::MapKey = "scaldor";
HexusOpponentData* Scaldor::HexusOpponentDataInstance = nullptr;
const std::string Scaldor::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_SCALDOR";

Scaldor* Scaldor::deserialize(ValueMap& properties)
{
	Scaldor* instance = new Scaldor(properties);

	instance->autorelease();

	return instance;
}

Scaldor::Scaldor(ValueMap& properties) : super(properties,
	Scaldor::MapKey,
	EntityResources::Npcs_DaemonsHallow_Scaldor_Animations,
	EntityResources::Npcs_DaemonsHallow_Scaldor_Emblem,
	Size(112.0f, 160.0f),
	1.05f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Scaldor::getHexusOpponentData();
}

Scaldor::~Scaldor()
{
}

Vec2 Scaldor::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Scaldor::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_DaemonsHallow_Scaldor::create();
}

HexusOpponentData* Scaldor::getHexusOpponentData()
{
	if (Scaldor::HexusOpponentDataInstance == nullptr)
	{
		Scaldor::HexusOpponentDataInstance = new HexusOpponentData(
			nullptr,
			HexusResources::Menus_HexusFrameDaemonsHallow,
			Vec2(-32.0f, -112.0f),
			Scaldor::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Fire,
			HexusOpponentData::generateDeck(32, 0.750f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Absorb),
				CardList::getInstance()->cardListByName.at(CardKeys::Absorb),
				CardList::getInstance()->cardListByName.at(CardKeys::Absorb),
				CardList::getInstance()->cardListByName.at(CardKeys::Addition),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
				CardList::getInstance()->cardListByName.at(CardKeys::BonusMoves),
			}),
			nullptr,
			nullptr
		);
	}

	return Scaldor::HexusOpponentDataInstance;
}