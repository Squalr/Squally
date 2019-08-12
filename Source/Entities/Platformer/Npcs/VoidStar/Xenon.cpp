#include "Xenon.h"

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

const std::string Xenon::MapKeyXenon = "xenon";
HexusOpponentData* Xenon::HexusOpponentDataInstance = nullptr;
const std::string Xenon::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_XENON";

Xenon* Xenon::deserialize(ValueMap& initProperties)
{
	Xenon* instance = new Xenon(initProperties);

	instance->autorelease();

	return instance;
}

Xenon::Xenon(ValueMap& initProperties) : NpcBase(initProperties,
	Xenon::MapKeyXenon,
	EntityResources::Npcs_VoidStar_Xenon_Animations,
	EntityResources::Npcs_VoidStar_Xenon_Emblem,
	Size(112.0f, 160.0f),
	0.85f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Xenon::getHexusOpponentData();
}

Xenon::~Xenon()
{
}

Vec2 Xenon::getAvatarFrameOffset()
{
	return Vec2(-32.0f, -112.0f);
}

HexusOpponentData* Xenon::getHexusOpponentData()
{
	if (Xenon::HexusOpponentDataInstance == nullptr)
	{
		Xenon::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Npcs_VoidStar_Xenon_Animations,
			HexusResources::Menus_HexusFrameVoidStar,
			0.85f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -112.0f),
			Xenon::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Shadow,
			0.904f,
			HexusOpponentData::generateDeck(32, 0.904f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				CardList::getInstance()->cardListByName.at(CardKeys::Flip4),
				CardList::getInstance()->cardListByName.at(CardKeys::SuddenDeath),
				CardList::getInstance()->cardListByName.at(CardKeys::Flip3),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),
				CardList::getInstance()->cardListByName.at(CardKeys::BonusMoves),

			}),
			nullptr
		);
	}

	return Xenon::HexusOpponentDataInstance;
}