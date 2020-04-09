#include "Ajax.h"

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

const std::string Ajax::MapKey = "ajax";
HexusOpponentData* Ajax::HexusOpponentDataInstance = nullptr;
const std::string Ajax::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_AJAX";

Ajax* Ajax::deserialize(ValueMap& properties)
{
	Ajax* instance = new Ajax(properties);

	instance->autorelease();

	return instance;
}

Ajax::Ajax(ValueMap& properties) : super(properties,
	Ajax::MapKey,
	EntityResources::Npcs_UnderflowRuins_Ajax_Animations,
	EntityResources::Npcs_UnderflowRuins_Ajax_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Ajax::getHexusOpponentData();
}

Ajax::~Ajax()
{
}

Vec2 Ajax::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Ajax::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_UnderflowRuins_Ajax::create();
}

HexusOpponentData* Ajax::getHexusOpponentData()
{
	if (Ajax::HexusOpponentDataInstance == nullptr)
	{
		Ajax::HexusOpponentDataInstance = new HexusOpponentData(
			nullptr,
			HexusResources::Menus_HexusFrameUnderflowRuins,
			Vec2(-32.0f, -112.0f),
			Ajax::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Light,
			HexusOpponentData::generateDeck(32, 0.152f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),
				CardList::getInstance()->cardListByName.at(CardKeys::Flip2),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
				CardList::getInstance()->cardListByName.at(CardKeys::Steal),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
			}),
			nullptr,
			nullptr
		);
	}

	return Ajax::HexusOpponentDataInstance;
}