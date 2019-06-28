//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED. ONLY EDIT NON-GENERATED SECTIONS. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Bancroft.h"

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

const std::string Bancroft::MapKeyBancroft = "bancroft";
HexusOpponentData* Bancroft::HexusOpponentDataInstance = nullptr;
const std::string Bancroft::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_BANCROFT";

Bancroft* Bancroft::deserialize(ValueMap& initProperties)
{
	Bancroft* instance = new Bancroft(initProperties);

	instance->autorelease();

	return instance;
}

Bancroft::Bancroft(ValueMap& initProperties) : NpcBase(initProperties,
	EntityResources::Npcs_VoidStar_Bancroft_Animations,
	EntityResources::Npcs_VoidStar_Bancroft_Emblem,
	PlatformerCollisionType::FriendlyNpc,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f),
	16,
	8)
{
	this->hexusOpponentData = Bancroft::getHexusOpponentData();
}

Bancroft::~Bancroft()
{
}

Vec2 Bancroft::getAvatarFrameOffset()
{
	return Vec2(-32.0f, -112.0f);
}

HexusOpponentData* Bancroft::getHexusOpponentData()
{
	if (Bancroft::HexusOpponentDataInstance == nullptr)
	{
		Bancroft::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Npcs_VoidStar_Bancroft_Animations,
			HexusResources::Menus_HexusFrameVoidStar,
			1.0f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -112.0f),
			Bancroft::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Shadow,
			0.913f,
			HexusOpponentData::generateDeck(32, 0.913f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Absorb),
				CardList::getInstance()->cardListByName.at(CardKeys::Subtraction),
				CardList::getInstance()->cardListByName.at(CardKeys::Steal),
				CardList::getInstance()->cardListByName.at(CardKeys::SuddenDeath),
				CardList::getInstance()->cardListByName.at(CardKeys::Flip4),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
				CardList::getInstance()->cardListByName.at(CardKeys::Subtraction),
				CardList::getInstance()->cardListByName.at(CardKeys::BonusMoves),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),

			}),
			nullptr
		);
	}

	return Bancroft::HexusOpponentDataInstance;
}