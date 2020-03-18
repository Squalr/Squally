#include "Marcel.h"

#include "cocos/math/CCGeometry.h"

#include "Scenes/Hexus/Card.h"
#include "Scenes/Hexus/CardData/CardData.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"
#include "Scenes/Hexus/StateOverride.h"

#include "Resources/EntityResources.h"
#include "Resources/HexusResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

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
	EntityResources::Npcs_EndianForest_Marcel_Animations,
	EntityResources::Npcs_EndianForest_Marcel_Emblem,
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
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Marcel::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_EndianForest_Marcel::create();
}

HexusOpponentData* Marcel::getHexusOpponentData()
{
	if (Marcel::HexusOpponentDataInstance == nullptr)
	{
		Marcel::HexusOpponentDataInstance = new HexusOpponentData(
			nullptr,
			HexusResources::Menus_HexusFrameEndianForest,
			Vec2(-32.0f, -112.0f),
			Marcel::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Shadow,
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
			nullptr,
			nullptr
		);
	}

	return Marcel::HexusOpponentDataInstance;
}