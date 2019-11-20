#include "Garrick.h"

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

#include "Strings/Platformer/Entities/Names/Npcs/LambdaCrypts/Garrick.h"

using namespace cocos2d;

const std::string Garrick::MapKeyGarrick = "garrick";
HexusOpponentData* Garrick::HexusOpponentDataInstance = nullptr;
const std::string Garrick::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_GARRICK";

Garrick* Garrick::deserialize(ValueMap& properties)
{
	Garrick* instance = new Garrick(properties);

	instance->autorelease();

	return instance;
}

Garrick::Garrick(ValueMap& properties) : super(properties,
	Garrick::MapKeyGarrick,
	EntityResources::Npcs_LambdaCrypts_Garrick_Animations,
	EntityResources::Npcs_LambdaCrypts_Garrick_Emblem,
	Size(112.0f, 160.0f),
	0.9f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Garrick::getHexusOpponentData();
}

Garrick::~Garrick()
{
}

Vec2 Garrick::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Garrick::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_LambdaCrypts_Garrick::create();
}

HexusOpponentData* Garrick::getHexusOpponentData()
{
	if (Garrick::HexusOpponentDataInstance == nullptr)
	{
		Garrick::HexusOpponentDataInstance = new HexusOpponentData(
			nullptr,
			HexusResources::Menus_HexusFrameLambdaCrypts,
			Vec2(-32.0f, -112.0f),
			Garrick::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Shadow,
			HexusOpponentData::generateDeck(32, 0.786f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::ReturnToHand),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
				CardList::getInstance()->cardListByName.at(CardKeys::Mov),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
				CardList::getInstance()->cardListByName.at(CardKeys::Subtraction),
				CardList::getInstance()->cardListByName.at(CardKeys::Inverse),
				CardList::getInstance()->cardListByName.at(CardKeys::Addition),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
			}),
			nullptr,
			nullptr
		);
	}

	return Garrick::HexusOpponentDataInstance;
}