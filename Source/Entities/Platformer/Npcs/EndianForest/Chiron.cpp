#include "Chiron.h"

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

#include "Strings/Platformer/Entities/Names/Npcs/EndianForest/Chiron.h"

using namespace cocos2d;

const std::string Chiron::MapKeyChiron = "chiron";
HexusOpponentData* Chiron::HexusOpponentDataInstance = nullptr;
const std::string Chiron::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_CHIRON";

Chiron* Chiron::deserialize(ValueMap& properties)
{
	Chiron* instance = new Chiron(properties);

	instance->autorelease();

	return instance;
}

Chiron::Chiron(ValueMap& properties) : super(properties,
	Chiron::MapKeyChiron,
	EntityResources::Npcs_EndianForest_Chiron_Animations,
	EntityResources::Npcs_EndianForest_Chiron_Emblem,
	Size(160.0f, 224.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Chiron::getHexusOpponentData();
}

Chiron::~Chiron()
{
}

Vec2 Chiron::getDialogueOffset()
{
	return Vec2(-48.0f, -32.0f);
}

LocalizedString* Chiron::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_EndianForest_Chiron::create();
}

HexusOpponentData* Chiron::getHexusOpponentData()
{
	if (Chiron::HexusOpponentDataInstance == nullptr)
	{
		Chiron::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Npcs_EndianForest_Chiron_Animations,
			HexusResources::Menus_HexusFrameEndianForest,
			1.0f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-48.0f, -128.0f),
			Chiron::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Earth,
			0.107f,
			HexusOpponentData::generateDeck(32, 0.107f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
				CardList::getInstance()->cardListByName.at(CardKeys::Flip1),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),
				CardList::getInstance()->cardListByName.at(CardKeys::Addition),
				CardList::getInstance()->cardListByName.at(CardKeys::Mov),
			}),
			{ },
			nullptr
		);
	}

	return Chiron::HexusOpponentDataInstance;
}