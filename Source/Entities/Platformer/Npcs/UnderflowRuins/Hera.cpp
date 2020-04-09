#include "Hera.h"

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

const std::string Hera::MapKey = "hera";
HexusOpponentData* Hera::HexusOpponentDataInstance = nullptr;
const std::string Hera::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_HERA";

Hera* Hera::deserialize(ValueMap& properties)
{
	Hera* instance = new Hera(properties);

	instance->autorelease();

	return instance;
}

Hera::Hera(ValueMap& properties) : super(properties,
	Hera::MapKey,
	EntityResources::Npcs_UnderflowRuins_Hera_Animations,
	EntityResources::Npcs_UnderflowRuins_Hera_Emblem,
	Size(112.0f, 160.0f),
	0.9f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Hera::getHexusOpponentData();
}

Hera::~Hera()
{
}

Vec2 Hera::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Hera::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_UnderflowRuins_Hera::create();
}

HexusOpponentData* Hera::getHexusOpponentData()
{
	if (Hera::HexusOpponentDataInstance == nullptr)
	{
		Hera::HexusOpponentDataInstance = new HexusOpponentData(
			nullptr,
			HexusResources::Menus_HexusFrameUnderflowRuins,
			Vec2(-32.0f, -112.0f),
			Hera::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Light,
			HexusOpponentData::generateDeck(32, 0.205f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				CardList::getInstance()->cardListByName.at(CardKeys::Mov),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
				CardList::getInstance()->cardListByName.at(CardKeys::Mov),
				CardList::getInstance()->cardListByName.at(CardKeys::ReturnToHand),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),
			}),
			nullptr,
			nullptr
		);
	}

	return Hera::HexusOpponentDataInstance;
}