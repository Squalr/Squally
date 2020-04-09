#include "Griffin.h"

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

const std::string Griffin::MapKey = "griffin";
HexusOpponentData* Griffin::HexusOpponentDataInstance = nullptr;
const std::string Griffin::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_GRIFFIN";

Griffin* Griffin::deserialize(ValueMap& properties)
{
	Griffin* instance = new Griffin(properties);

	instance->autorelease();

	return instance;
}

Griffin::Griffin(ValueMap& properties) : super(properties,
	Griffin::MapKey,
	EntityResources::Npcs_UnderflowRuins_Griffin_Animations,
	EntityResources::Npcs_UnderflowRuins_Griffin_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Griffin::getHexusOpponentData();
}

Griffin::~Griffin()
{
}

Vec2 Griffin::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Griffin::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_UnderflowRuins_Griffin::create();
}

HexusOpponentData* Griffin::getHexusOpponentData()
{
	if (Griffin::HexusOpponentDataInstance == nullptr)
	{
		Griffin::HexusOpponentDataInstance = new HexusOpponentData(
			nullptr,
			HexusResources::Menus_HexusFrameUnderflowRuins,
			Vec2(-32.0f, -112.0f),
			Griffin::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Light,
			HexusOpponentData::generateDeck(32, 0.188f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Addition),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
				CardList::getInstance()->cardListByName.at(CardKeys::Addition),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),
				CardList::getInstance()->cardListByName.at(CardKeys::Flip2),
			}),
			nullptr,
			nullptr
		);
	}

	return Griffin::HexusOpponentDataInstance;
}