#include "Illia.h"

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

#include "Strings/Platformer/Entities/Names/Npcs/VoidStar/Illia.h"

using namespace cocos2d;

const std::string Illia::MapKeyIllia = "illia";
HexusOpponentData* Illia::HexusOpponentDataInstance = nullptr;
const std::string Illia::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_ILLIA";

Illia* Illia::deserialize(ValueMap& properties)
{
	Illia* instance = new Illia(properties);

	instance->autorelease();

	return instance;
}

Illia::Illia(ValueMap& properties) : super(properties,
	Illia::MapKeyIllia,
	EntityResources::Npcs_VoidStar_Illia_Animations,
	EntityResources::Npcs_VoidStar_Illia_Emblem,
	Size(112.0f, 160.0f),
	0.85f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Illia::getHexusOpponentData();
}

Illia::~Illia()
{
}

Vec2 Illia::getDialogueOffset()
{
	return Vec2(-32.0f, -112.0f);
}

LocalizedString* Illia::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_VoidStar_Illia::create();
}

HexusOpponentData* Illia::getHexusOpponentData()
{
	if (Illia::HexusOpponentDataInstance == nullptr)
	{
		Illia::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Npcs_VoidStar_Illia_Animations,
			HexusResources::Menus_HexusFrameVoidStar,
			0.85f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -112.0f),
			Illia::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Shadow,
			0.981f,
			HexusOpponentData::generateDeck(32, 0.981f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				CardList::getInstance()->cardListByName.at(CardKeys::Flip4),
				CardList::getInstance()->cardListByName.at(CardKeys::Flip3),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
				CardList::getInstance()->cardListByName.at(CardKeys::Inverse),
				CardList::getInstance()->cardListByName.at(CardKeys::Inverse),
				CardList::getInstance()->cardListByName.at(CardKeys::Flip4),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),

			}),
			nullptr
		);
	}

	return Illia::HexusOpponentDataInstance;
}