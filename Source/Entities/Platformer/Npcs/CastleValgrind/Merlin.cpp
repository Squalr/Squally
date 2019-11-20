#include "Merlin.h"

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

#include "Strings/Platformer/Entities/Names/Npcs/CastleValgrind/Merlin.h"

using namespace cocos2d;

const std::string Merlin::MapKeyMerlin = "merlin";
HexusOpponentData* Merlin::HexusOpponentDataInstance = nullptr;
const std::string Merlin::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_MERLIN";

Merlin* Merlin::deserialize(ValueMap& properties)
{
	Merlin* instance = new Merlin(properties);

	instance->autorelease();

	return instance;
}

Merlin::Merlin(ValueMap& properties) : super(properties,
	Merlin::MapKeyMerlin,
	nullptr,
	EntityResources::Npcs_CastleValgrind_Merlin_Emblem,
	Size(112.0f, 160.0f),
	1.05f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Merlin::getHexusOpponentData();
}

Merlin::~Merlin()
{
}

Vec2 Merlin::getDialogueOffset()
{
	return Vec2(0.0f, -32.0f);
}

LocalizedString* Merlin::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_CastleValgrind_Merlin::create();
}

HexusOpponentData* Merlin::getHexusOpponentData()
{
	if (Merlin::HexusOpponentDataInstance == nullptr)
	{
		Merlin::HexusOpponentDataInstance = new HexusOpponentData(
			nullptr,
			HexusResources::Menus_HexusFrameCastleValgrind,
			Vec2(-32.0f, -112.0f),
			Merlin::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Air,
			HexusOpponentData::generateDeck(32, 0.438f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Steal),
				CardList::getInstance()->cardListByName.at(CardKeys::ReturnToHand),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
				CardList::getInstance()->cardListByName.at(CardKeys::Flip2),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
			}),
			nullptr,
			nullptr
		);
	}

	return Merlin::HexusOpponentDataInstance;
}