#include "Mara.h"

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

#include "Strings/Platformer/Entities/Names/Npcs/VoidStar/Mara.h"

using namespace cocos2d;

const std::string Mara::MapKeyMara = "mara";
HexusOpponentData* Mara::HexusOpponentDataInstance = nullptr;
const std::string Mara::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_MARA";

Mara* Mara::deserialize(ValueMap& properties)
{
	Mara* instance = new Mara(properties);

	instance->autorelease();

	return instance;
}

Mara::Mara(ValueMap& properties) : super(properties,
	Mara::MapKeyMara,
	nullptr,
	EntityResources::Npcs_VoidStar_Mara_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Mara::getHexusOpponentData();
}

Mara::~Mara()
{
}

Vec2 Mara::getDialogueOffset()
{
	return Vec2(0.0f, -32.0f);
}

LocalizedString* Mara::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_VoidStar_Mara::create();
}

HexusOpponentData* Mara::getHexusOpponentData()
{
	if (Mara::HexusOpponentDataInstance == nullptr)
	{
		Mara::HexusOpponentDataInstance = new HexusOpponentData(
			nullptr,
			HexusResources::Menus_HexusFrameVoidStar,
			Vec2(-32.0f, -112.0f),
			Mara::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Shadow,
			HexusOpponentData::generateDeck(32, 0.962f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				CardList::getInstance()->cardListByName.at(CardKeys::Kill),
				CardList::getInstance()->cardListByName.at(CardKeys::Kill),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Steal),
				CardList::getInstance()->cardListByName.at(CardKeys::Mov),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
			}),
			nullptr,
			nullptr
		);
	}

	return Mara::HexusOpponentDataInstance;
}