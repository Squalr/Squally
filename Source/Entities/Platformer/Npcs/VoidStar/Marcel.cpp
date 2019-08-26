#include "Marcel.h"

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

#include "Strings/Platformer/Entities/Names/Npcs/VoidStar/Marcel.h"

using namespace cocos2d;

const std::string Marcel::MapKeyMarcel = "marcel";
HexusOpponentData* Marcel::HexusOpponentDataInstance = nullptr;
const std::string Marcel::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_MARCEL";

Marcel* Marcel::deserialize(ValueMap& properties)
{
	Marcel* instance = new Marcel(properties);

	instance->autorelease();

	return instance;
}

Marcel::Marcel(ValueMap& properties) : super(properties,
	Marcel::MapKeyMarcel,
	EntityResources::Npcs_VoidStar_Marcel_Animations,
	EntityResources::Npcs_VoidStar_Marcel_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Marcel::getHexusOpponentData();
}

Marcel::~Marcel()
{
}

Vec2 Marcel::getDialogueOffset()
{
	return Vec2(0.0f, -32.0f);
}

LocalizedString* Marcel::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_VoidStar_Marcel::create();
}

HexusOpponentData* Marcel::getHexusOpponentData()
{
	if (Marcel::HexusOpponentDataInstance == nullptr)
	{
		Marcel::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Npcs_VoidStar_Marcel_Animations,
			HexusResources::Menus_HexusFrameVoidStar,
			1.0f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -112.0f),
			Marcel::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Shadow,
			0.952f,
			HexusOpponentData::generateDeck(32, 0.952f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::ReturnToHand),
				CardList::getInstance()->cardListByName.at(CardKeys::Addition),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
				CardList::getInstance()->cardListByName.at(CardKeys::Inverse),
				CardList::getInstance()->cardListByName.at(CardKeys::Flip4),
				CardList::getInstance()->cardListByName.at(CardKeys::Absorb),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
				CardList::getInstance()->cardListByName.at(CardKeys::Steal),

			}),
			nullptr
		);
	}

	return Marcel::HexusOpponentDataInstance;
}