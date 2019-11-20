#include "Ara.h"

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

#include "Strings/Platformer/Entities/Names/Npcs/EndianForest/Ara.h"

using namespace cocos2d;

const std::string Ara::MapKeyAra = "ara";
HexusOpponentData* Ara::HexusOpponentDataInstance = nullptr;
const std::string Ara::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_ARA";

Ara* Ara::deserialize(ValueMap& properties)
{
	Ara* instance = new Ara(properties);

	instance->autorelease();

	return instance;
}

Ara::Ara(ValueMap& properties) : super(properties,
	Ara::MapKeyAra,
	EntityResources::Npcs_EndianForest_Ara_Animations,
	EntityResources::Npcs_EndianForest_Ara_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Ara::getHexusOpponentData();
}

Ara::~Ara()
{
}

Vec2 Ara::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Ara::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_EndianForest_Ara::create();
}

HexusOpponentData* Ara::getHexusOpponentData()
{
	if (Ara::HexusOpponentDataInstance == nullptr)
	{
		Ara::HexusOpponentDataInstance = new HexusOpponentData(
			nullptr,
			HexusResources::Menus_HexusFrameEndianForest,
			Vec2(-32.0f, -112.0f),
			Ara::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Earth,
			HexusOpponentData::generateDeck(32, 0.125f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				CardList::getInstance()->cardListByName.at(CardKeys::Steal),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
			}),
			nullptr,
			nullptr
		);
	}

	return Ara::HexusOpponentDataInstance;
}