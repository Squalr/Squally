#include "Godiva.h"

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

#include "Strings/Platformer/Entities/Names/Npcs/VoidStar/Godiva.h"

using namespace cocos2d;

const std::string Godiva::MapKeyGodiva = "godiva";
HexusOpponentData* Godiva::HexusOpponentDataInstance = nullptr;
const std::string Godiva::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_GODIVA";

Godiva* Godiva::deserialize(ValueMap& properties)
{
	Godiva* instance = new Godiva(properties);

	instance->autorelease();

	return instance;
}

Godiva::Godiva(ValueMap& properties) : super(properties,
	Godiva::MapKeyGodiva,
	nullptr,
	EntityResources::Npcs_VoidStar_Godiva_Emblem,
	Size(112.0f, 160.0f),
	1.05f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Godiva::getHexusOpponentData();
}

Godiva::~Godiva()
{
}

Vec2 Godiva::getDialogueOffset()
{
	return Vec2(0.0f, -32.0f);
}

LocalizedString* Godiva::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_VoidStar_Godiva::create();
}

HexusOpponentData* Godiva::getHexusOpponentData()
{
	if (Godiva::HexusOpponentDataInstance == nullptr)
	{
		Godiva::HexusOpponentDataInstance = new HexusOpponentData(
			nullptr,
			HexusResources::Menus_HexusFrameVoidStar,
			Vec2(-32.0f, -112.0f),
			Godiva::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Shadow,
			HexusOpponentData::generateDeck(32, 0.990f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
				CardList::getInstance()->cardListByName.at(CardKeys::Kill),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),
				CardList::getInstance()->cardListByName.at(CardKeys::SuddenDeath),
				CardList::getInstance()->cardListByName.at(CardKeys::ReturnToHand),
				CardList::getInstance()->cardListByName.at(CardKeys::Absorb),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
				CardList::getInstance()->cardListByName.at(CardKeys::Flip3),
			}),
			nullptr,
			nullptr
		);
	}

	return Godiva::HexusOpponentDataInstance;
}