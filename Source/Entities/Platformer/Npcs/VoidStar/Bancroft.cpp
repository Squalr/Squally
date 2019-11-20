#include "Bancroft.h"

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

#include "Strings/Platformer/Entities/Names/Npcs/VoidStar/Bancroft.h"

using namespace cocos2d;

const std::string Bancroft::MapKeyBancroft = "bancroft";
HexusOpponentData* Bancroft::HexusOpponentDataInstance = nullptr;
const std::string Bancroft::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_BANCROFT";

Bancroft* Bancroft::deserialize(ValueMap& properties)
{
	Bancroft* instance = new Bancroft(properties);

	instance->autorelease();

	return instance;
}

Bancroft::Bancroft(ValueMap& properties) : super(properties,
	Bancroft::MapKeyBancroft,
	EntityResources::Npcs_VoidStar_Bancroft_Animations,
	EntityResources::Npcs_VoidStar_Bancroft_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Bancroft::getHexusOpponentData();
}

Bancroft::~Bancroft()
{
}

Vec2 Bancroft::getDialogueOffset()
{
	return Vec2(0.0f, -32.0f);
}

LocalizedString* Bancroft::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_VoidStar_Bancroft::create();
}

HexusOpponentData* Bancroft::getHexusOpponentData()
{
	if (Bancroft::HexusOpponentDataInstance == nullptr)
	{
		Bancroft::HexusOpponentDataInstance = new HexusOpponentData(
			nullptr,
			HexusResources::Menus_HexusFrameVoidStar,
			Vec2(-32.0f, -112.0f),
			Bancroft::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Shadow,
			HexusOpponentData::generateDeck(32, 0.913f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Absorb),
				CardList::getInstance()->cardListByName.at(CardKeys::Subtraction),
				CardList::getInstance()->cardListByName.at(CardKeys::Steal),
				CardList::getInstance()->cardListByName.at(CardKeys::SuddenDeath),
				CardList::getInstance()->cardListByName.at(CardKeys::Flip4),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
				CardList::getInstance()->cardListByName.at(CardKeys::Subtraction),
				CardList::getInstance()->cardListByName.at(CardKeys::BonusMoves),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),
			}),
			nullptr,
			nullptr
		);
	}

	return Bancroft::HexusOpponentDataInstance;
}