//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED. ONLY EDIT NON-GENERATED SECTIONS. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Celeste.h"

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

using namespace cocos2d;

const std::string Celeste::MapKeyCeleste = "celeste";
HexusOpponentData* Celeste::HexusOpponentDataInstance = nullptr;
const std::string Celeste::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_CELESTE";

Celeste* Celeste::deserialize(ValueMap& initProperties)
{
	Celeste* instance = new Celeste(initProperties);

	instance->autorelease();

	return instance;
}

Celeste::Celeste(ValueMap& initProperties) : NpcBase(initProperties,
	EntityResources::Npcs_DaemonsHallow_Celeste_Animations,
	EntityResources::Npcs_DaemonsHallow_Celeste_Emblem,
	PlatformerCollisionType::FriendlyNpc,
	Size(112.0f, 160.0f),
	0.85f,
	Vec2(0.0f, 0.0f),
	16,
	8)
{
	this->hexusOpponentData = Celeste::getHexusOpponentData();
}

Celeste::~Celeste()
{
}

Vec2 Celeste::getAvatarFrameOffset()
{
	return Vec2(-32.0f, -112.0f);
}

HexusOpponentData* Celeste::getHexusOpponentData()
{
	if (Celeste::HexusOpponentDataInstance == nullptr)
	{
		Celeste::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Npcs_DaemonsHallow_Celeste_Animations,
			HexusResources::Menus_HexusFrameDaemonsHallow,
			0.85f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -112.0f),
			Celeste::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Fire,
			0.670f,
			HexusOpponentData::generateDeck(32, 0.670f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Addition),
				CardList::getInstance()->cardListByName.at(CardKeys::Absorb),
				CardList::getInstance()->cardListByName.at(CardKeys::Kill),
				CardList::getInstance()->cardListByName.at(CardKeys::Mov),
				CardList::getInstance()->cardListByName.at(CardKeys::Steal),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),

			}),
			nullptr
		);
	}

	return Celeste::HexusOpponentDataInstance;
}