#include "Zana.h"

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

using namespace cocos2d;

const std::string Zana::MapKeyZana = "zana";
HexusOpponentData* Zana::HexusOpponentDataInstance = nullptr;
const std::string Zana::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_ZANA";

Zana* Zana::deserialize(ValueMap& properties)
{
	Zana* instance = new Zana(properties);

	instance->autorelease();

	return instance;
}

Zana::Zana(ValueMap& properties) : super(properties,
	Zana::MapKeyZana,
	EntityResources::Npcs_LambdaCrypts_Zana_Animations,
	EntityResources::Npcs_LambdaCrypts_Zana_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Zana::getHexusOpponentData();
}

Zana::~Zana()
{
}

Vec2 Zana::getDialogueOffset()
{
	return Vec2(-32.0f, -112.0f);
}

LocalizedString* Zana::getEntityName()
{
	return nullptr;
}

HexusOpponentData* Zana::getHexusOpponentData()
{
	if (Zana::HexusOpponentDataInstance == nullptr)
	{
		Zana::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Npcs_LambdaCrypts_Zana_Animations,
			HexusResources::Menus_HexusFrameLambdaCrypts,
			1.0f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -112.0f),
			Zana::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Shadow,
			0.830f,
			HexusOpponentData::generateDeck(32, 0.830f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				CardList::getInstance()->cardListByName.at(CardKeys::BonusMoves),
				CardList::getInstance()->cardListByName.at(CardKeys::Steal),
				CardList::getInstance()->cardListByName.at(CardKeys::Mov),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
				CardList::getInstance()->cardListByName.at(CardKeys::ReturnToHand),
				CardList::getInstance()->cardListByName.at(CardKeys::Kill),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),

			}),
			nullptr
		);
	}

	return Zana::HexusOpponentDataInstance;
}