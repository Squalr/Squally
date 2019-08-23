#include "Jasper.h"

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

using namespace cocos2d;

const std::string Jasper::MapKeyJasper = "jasper";
HexusOpponentData* Jasper::HexusOpponentDataInstance = nullptr;
const std::string Jasper::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_JASPER";

Jasper* Jasper::deserialize(ValueMap& properties)
{
	Jasper* instance = new Jasper(properties);

	instance->autorelease();

	return instance;
}

Jasper::Jasper(ValueMap& properties) : super(properties,
	Jasper::MapKeyJasper,
	EntityResources::Npcs_SeaSharpCaverns_Jasper_Animations,
	EntityResources::Npcs_SeaSharpCaverns_Jasper_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Jasper::getHexusOpponentData();
}

Jasper::~Jasper()
{
}

Vec2 Jasper::getDialogueOffset()
{
	return Vec2(-32.0f, -112.0f);
}

LocalizedString* Jasper::getEntityName()
{
	return nullptr;
}

HexusOpponentData* Jasper::getHexusOpponentData()
{
	if (Jasper::HexusOpponentDataInstance == nullptr)
	{
		Jasper::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Npcs_SeaSharpCaverns_Jasper_Animations,
			HexusResources::Menus_HexusFrameSeaSharpCaverns,
			1.0f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -112.0f),
			Jasper::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Earth,
			0.321f,
			HexusOpponentData::generateDeck(32, 0.321f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
				CardList::getInstance()->cardListByName.at(CardKeys::ReturnToHand),
				CardList::getInstance()->cardListByName.at(CardKeys::Steal),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),

			}),
			nullptr
		);
	}

	return Jasper::HexusOpponentDataInstance;
}