#include "Gramps.h"

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

const std::string Gramps::MapKeyGramps = "gramps";
HexusOpponentData* Gramps::HexusOpponentDataInstance = nullptr;
const std::string Gramps::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_GRAMPS";

Gramps* Gramps::deserialize(ValueMap& properties)
{
	Gramps* instance = new Gramps(properties);

	instance->autorelease();

	return instance;
}

Gramps::Gramps(ValueMap& properties) : super(properties,
	Gramps::MapKeyGramps,
	EntityResources::Npcs_EndianForest_Gramps_Animations,
	EntityResources::Npcs_EndianForest_Gramps_Emblem,
	Size(112.0f, 160.0f),
	0.85f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Gramps::getHexusOpponentData();
}

Gramps::~Gramps()
{
}

Vec2 Gramps::getDialogueOffset()
{
	return Vec2(-32.0f, -112.0f);
}

LocalizedString* Gramps::getEntityName()
{
	return nullptr;
}

HexusOpponentData* Gramps::getHexusOpponentData()
{
	if (Gramps::HexusOpponentDataInstance == nullptr)
	{
		Gramps::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Npcs_EndianForest_Gramps_Animations,
			HexusResources::Menus_HexusFrameEndianForest,
			0.85f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -112.0f),
			Gramps::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Earth,
			0.080f,
			HexusOpponentData::generateDeck(32, 0.080f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Flip2),
				CardList::getInstance()->cardListByName.at(CardKeys::Flip1),
				CardList::getInstance()->cardListByName.at(CardKeys::Addition),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),

			}),
			nullptr
		);
	}

	return Gramps::HexusOpponentDataInstance;
}