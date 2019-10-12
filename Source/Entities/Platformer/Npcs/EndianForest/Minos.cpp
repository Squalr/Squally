#include "Minos.h"

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

#include "Strings/Platformer/Entities/Names/Npcs/EndianForest/Minos.h"

using namespace cocos2d;

const std::string Minos::MapKeyMinos = "minos";
HexusOpponentData* Minos::HexusOpponentDataInstance = nullptr;
const std::string Minos::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_MINOS";

Minos* Minos::deserialize(ValueMap& properties)
{
	Minos* instance = new Minos(properties);

	instance->autorelease();

	return instance;
}

Minos::Minos(ValueMap& properties) : super(properties,
	Minos::MapKeyMinos,
	EntityResources::Npcs_EndianForest_Minos_Animations,
	EntityResources::Npcs_EndianForest_Minos_Emblem,
	Size(112.0f, 160.0f),
	1.1f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Minos::getHexusOpponentData();
}

Minos::~Minos()
{
}

Vec2 Minos::getDialogueOffset()
{
	return Vec2(0.0f, -32.0f);
}

LocalizedString* Minos::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_EndianForest_Minos::create();
}

HexusOpponentData* Minos::getHexusOpponentData()
{
	if (Minos::HexusOpponentDataInstance == nullptr)
	{
		Minos::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Npcs_EndianForest_Minos_Animations,
			HexusResources::Menus_HexusFrameEndianForest,
			1.1f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -112.0f),
			Minos::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Earth,
			0.062f,
			HexusOpponentData::generateDeck(32, 0.062f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				CardList::getInstance()->cardListByName.at(CardKeys::Mov),
				CardList::getInstance()->cardListByName.at(CardKeys::Flip1),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
				CardList::getInstance()->cardListByName.at(CardKeys::Flip2),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
			}),
			nullptr,
			nullptr
		);
	}

	return Minos::HexusOpponentDataInstance;
}