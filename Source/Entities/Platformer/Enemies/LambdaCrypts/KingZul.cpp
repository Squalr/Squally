#include "KingZul.h"

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

const std::string KingZul::MapKey = "king-zul";
HexusOpponentData* KingZul::HexusOpponentDataInstance = nullptr;
const std::string KingZul::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_KING_ZUL";

KingZul* KingZul::deserialize(ValueMap& properties)
{
	KingZul* instance = new KingZul(properties);

	instance->autorelease();

	return instance;
}

KingZul::KingZul(ValueMap& properties) : super(properties,
	KingZul::MapKey,
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
	return Vec2(0.0f, 0.0f);
}

LocalizedString* KingZul::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_LambdaCrypts_KingZul::create();
}

HexusOpponentData* KingZul::getHexusOpponentData()
{
	if (KingZul::HexusOpponentDataInstance == nullptr)
	{
		KingZul::HexusOpponentDataInstance = new HexusOpponentData(
			nullptr,
			HexusResources::Menus_HexusFrameLambdaCrypts,
			Vec2(-32.0f, -112.0f),
			KingZul::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Shadow,
			HexusOpponentData::generateDeck(32, 1.000f,
			{

			}),
			nullptr,
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
					
				}
			)
		);
	}

	return KingZul::HexusOpponentDataInstance;
}