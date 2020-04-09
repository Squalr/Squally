#include "Thor.h"

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

const std::string Thor::MapKey = "thor";
HexusOpponentData* Thor::HexusOpponentDataInstance = nullptr;
const std::string Thor::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_THOR";

Thor* Thor::deserialize(ValueMap& properties)
{
	Thor* instance = new Thor(properties);

	instance->autorelease();

	return instance;
}

Thor::Thor(ValueMap& properties) : super(properties,
	Thor::MapKey,
	EntityResources::Npcs_UnderflowRuins_Thor_Animations,
	EntityResources::Npcs_UnderflowRuins_Thor_Emblem,
	Size(112.0f, 160.0f),
	0.9f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Thor::getHexusOpponentData();
}

Thor::~Thor()
{
}

Vec2 Thor::getDialogueOffset()
{
	return Vec2(-32.0f, -144.0f);
}

LocalizedString* Thor::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_UnderflowRuins_Thor::create();
}

HexusOpponentData* Thor::getHexusOpponentData()
{
	if (Thor::HexusOpponentDataInstance == nullptr)
	{
		Thor::HexusOpponentDataInstance = new HexusOpponentData(
			nullptr,
			HexusResources::Menus_HexusFrameUnderflowRuins,
			Vec2(-32.0f, -144.0f),
			Thor::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Light,
			HexusOpponentData::generateDeck(32, 0.241f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
				CardList::getInstance()->cardListByName.at(CardKeys::Mov),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
			}),
			nullptr,
			nullptr
		);
	}

	return Thor::HexusOpponentDataInstance;
}