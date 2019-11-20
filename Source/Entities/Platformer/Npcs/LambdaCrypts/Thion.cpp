#include "Thion.h"

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

#include "Strings/Platformer/Entities/Names/Npcs/LambdaCrypts/Thion.h"

using namespace cocos2d;

const std::string Thion::MapKeyThion = "thion";
HexusOpponentData* Thion::HexusOpponentDataInstance = nullptr;
const std::string Thion::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_THION";

Thion* Thion::deserialize(ValueMap& properties)
{
	Thion* instance = new Thion(properties);

	instance->autorelease();

	return instance;
}

Thion::Thion(ValueMap& properties) : super(properties,
	Thion::MapKeyThion,
	EntityResources::Npcs_LambdaCrypts_Thion_Animations,
	EntityResources::Npcs_LambdaCrypts_Thion_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Thion::getHexusOpponentData();
}

Thion::~Thion()
{
}

Vec2 Thion::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Thion::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_LambdaCrypts_Thion::create();
}

HexusOpponentData* Thion::getHexusOpponentData()
{
	if (Thion::HexusOpponentDataInstance == nullptr)
	{
		Thion::HexusOpponentDataInstance = new HexusOpponentData(
			nullptr,
			HexusResources::Menus_HexusFrameLambdaCrypts,
			Vec2(-32.0f, -112.0f),
			Thion::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Shadow,
			HexusOpponentData::generateDeck(32, 0.857f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::SuddenDeath),
				CardList::getInstance()->cardListByName.at(CardKeys::Flip3),
				CardList::getInstance()->cardListByName.at(CardKeys::Flip3),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				CardList::getInstance()->cardListByName.at(CardKeys::BonusMoves),
				CardList::getInstance()->cardListByName.at(CardKeys::Absorb),
				CardList::getInstance()->cardListByName.at(CardKeys::Addition),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
			}),
			nullptr,
			nullptr
		);
	}

	return Thion::HexusOpponentDataInstance;
}