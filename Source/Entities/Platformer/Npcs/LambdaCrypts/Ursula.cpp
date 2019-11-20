#include "Ursula.h"

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

#include "Strings/Platformer/Entities/Names/Npcs/LambdaCrypts/Ursula.h"

using namespace cocos2d;

const std::string Ursula::MapKeyUrsula = "ursula";
HexusOpponentData* Ursula::HexusOpponentDataInstance = nullptr;
const std::string Ursula::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_URSULA";

Ursula* Ursula::deserialize(ValueMap& properties)
{
	Ursula* instance = new Ursula(properties);

	instance->autorelease();

	return instance;
}

Ursula::Ursula(ValueMap& properties) : super(properties,
	Ursula::MapKeyUrsula,
	EntityResources::Npcs_LambdaCrypts_Ursula_Animations,
	EntityResources::Npcs_LambdaCrypts_Ursula_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Ursula::getHexusOpponentData();
}

Ursula::~Ursula()
{
}

Vec2 Ursula::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Ursula::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_LambdaCrypts_Ursula::create();
}

HexusOpponentData* Ursula::getHexusOpponentData()
{
	if (Ursula::HexusOpponentDataInstance == nullptr)
	{
		Ursula::HexusOpponentDataInstance = new HexusOpponentData(
			nullptr,
			HexusResources::Menus_HexusFrameLambdaCrypts,
			Vec2(-32.0f, -112.0f),
			Ursula::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Shadow,
			HexusOpponentData::generateDeck(32, 0.839f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Flip3),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
				CardList::getInstance()->cardListByName.at(CardKeys::Steal),
				CardList::getInstance()->cardListByName.at(CardKeys::SuddenDeath),
				CardList::getInstance()->cardListByName.at(CardKeys::Inverse),
				CardList::getInstance()->cardListByName.at(CardKeys::Steal),
				CardList::getInstance()->cardListByName.at(CardKeys::Flip3),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),
			}),
			nullptr,
			nullptr
		);
	}

	return Ursula::HexusOpponentDataInstance;
}