#include "Radon.h"

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

#include "Strings/Platformer/Entities/Names/Npcs/VoidStar/Radon.h"

using namespace cocos2d;

const std::string Radon::MapKeyRadon = "radon";
HexusOpponentData* Radon::HexusOpponentDataInstance = nullptr;
const std::string Radon::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_RADON";

Radon* Radon::deserialize(ValueMap& properties)
{
	Radon* instance = new Radon(properties);

	instance->autorelease();

	return instance;
}

Radon::Radon(ValueMap& properties) : super(properties,
	Radon::MapKeyRadon,
	EntityResources::Npcs_VoidStar_Radon_Animations,
	EntityResources::Npcs_VoidStar_Radon_Emblem,
	Size(112.0f, 160.0f),
	0.85f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Radon::getHexusOpponentData();
}

Radon::~Radon()
{
}

Vec2 Radon::getDialogueOffset()
{
	return Vec2(0.0f, -32.0f);
}

LocalizedString* Radon::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_VoidStar_Radon::create();
}

HexusOpponentData* Radon::getHexusOpponentData()
{
	if (Radon::HexusOpponentDataInstance == nullptr)
	{
		Radon::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Npcs_VoidStar_Radon_Animations,
			HexusResources::Menus_HexusFrameVoidStar,
			0.85f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -112.0f),
			Radon::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Shadow,
			0.923f,
			HexusOpponentData::generateDeck(32, 0.923f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Flip4),
				CardList::getInstance()->cardListByName.at(CardKeys::Absorb),
				CardList::getInstance()->cardListByName.at(CardKeys::Inverse),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
				CardList::getInstance()->cardListByName.at(CardKeys::SuddenDeath),
				CardList::getInstance()->cardListByName.at(CardKeys::Subtraction),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
				CardList::getInstance()->cardListByName.at(CardKeys::Steal),
			}),
			nullptr,
			nullptr
		);
	}

	return Radon::HexusOpponentDataInstance;
}