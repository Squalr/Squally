#include "QueenElise.h"

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

#include "Strings/Platformer/Entities/Names/Npcs/VoidStar/QueenElise.h"

using namespace cocos2d;

const std::string QueenElise::MapKeyQueenElise = "queen-elise";
HexusOpponentData* QueenElise::HexusOpponentDataInstance = nullptr;
const std::string QueenElise::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_QUEEN_ELISE";

QueenElise* QueenElise::deserialize(ValueMap& properties)
{
	QueenElise* instance = new QueenElise(properties);

	instance->autorelease();

	return instance;
}

QueenElise::QueenElise(ValueMap& properties) : super(properties,
	QueenElise::MapKeyQueenElise,
	EntityResources::Npcs_VoidStar_QueenElise_Animations,
	EntityResources::Npcs_VoidStar_QueenElise_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = QueenElise::getHexusOpponentData();
}

QueenElise::~QueenElise()
{
}

Vec2 QueenElise::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* QueenElise::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_VoidStar_QueenElise::create();
}

HexusOpponentData* QueenElise::getHexusOpponentData()
{
	if (QueenElise::HexusOpponentDataInstance == nullptr)
	{
		QueenElise::HexusOpponentDataInstance = new HexusOpponentData(
			nullptr,
			HexusResources::Menus_HexusFrameVoidStar,
			Vec2(-32.0f, -112.0f),
			QueenElise::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Shadow,
			HexusOpponentData::generateDeck(32, 0.933f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::SuddenDeath),
				CardList::getInstance()->cardListByName.at(CardKeys::Steal),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),
				CardList::getInstance()->cardListByName.at(CardKeys::Mov),
				CardList::getInstance()->cardListByName.at(CardKeys::BonusMoves),
				CardList::getInstance()->cardListByName.at(CardKeys::Steal),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
			}),
			nullptr,
			nullptr
		);
	}

	return QueenElise::HexusOpponentDataInstance;
}