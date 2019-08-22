#include "KingZul.h"

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

const std::string KingZul::MapKeyKingZul = "king-zul";
HexusOpponentData* KingZul::HexusOpponentDataInstance = nullptr;
const std::string KingZul::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_KING_ZUL";

KingZul* KingZul::deserialize(ValueMap& properties)
{
	KingZul* instance = new KingZul(properties);

	instance->autorelease();

	return instance;
}

KingZul::KingZul(ValueMap& properties) : PlatformerEnemy(properties,
	KingZul::MapKeyKingZul,
	EntityResources::Enemies_LambdaCrypts_KingZul_Animations,
	EntityResources::Enemies_LambdaCrypts_KingZul_Emblem,
	Size(196.0f, 320.0f),
	0.9f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = KingZul::getHexusOpponentData();
}

KingZul::~KingZul()
{
}

Vec2 KingZul::getDialogueOffset()
{
	return Vec2(-32.0f, -112.0f);
}

HexusOpponentData* KingZul::getHexusOpponentData()
{
	if (KingZul::HexusOpponentDataInstance == nullptr)
	{
		KingZul::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Enemies_LambdaCrypts_KingZul_Animations,
			HexusResources::Menus_HexusFrameLambdaCrypts,
			0.9f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -112.0f),
			KingZul::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Shadow,
			1.000f,
			HexusOpponentData::generateDeck(32, 1.000f,
			{

			}),
			StateOverride::create(
				// Player losses
				1,
				// Enemy losses
				1,
				// Player's turn
				true,
				// Player passed
				true,
				// Enemy passed
				true,
				// Player deck
				std::vector<CardData*>
				{
					
				},
				// Enemy deck
				std::vector<CardData*>
				{
					
				},
				// Player hand
				std::vector<CardData*>
				{
					
				},
				// Enemy hand
				std::vector<CardData*>
				{
					
				},
				// Player binary cards
				std::vector<CardData*>
				{
					
				},
				// Player decimal cards
				std::vector<CardData*>
				{
					
				},
				// Player hex cards
				std::vector<CardData*>
				{
					
				},
				// Enemy binary cards
				std::vector<CardData*>
				{
					
				},
				// Enemy decimal cards
				std::vector<CardData*>
				{
					
				},
				// Enemy hex cards
				std::vector<CardData*>
				{
					
				},
				StateOverride::TutorialMode::NoTutorial
			)
		);
	}

	return KingZul::HexusOpponentDataInstance;
}