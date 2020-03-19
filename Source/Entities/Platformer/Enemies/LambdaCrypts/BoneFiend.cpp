#include "BoneFiend.h"

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

const std::string BoneFiend::MapKey = "bone-fiend";
HexusOpponentData* BoneFiend::HexusOpponentDataInstance = nullptr;
const std::string BoneFiend::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_BONE_FIEND";

BoneFiend* BoneFiend::deserialize(ValueMap& properties)
{
	BoneFiend* instance = new BoneFiend(properties);

	instance->autorelease();

	return instance;
}

BoneFiend::BoneFiend(ValueMap& properties) : super(properties,
	BoneFiend::MapKey,
	EntityResources::Enemies_LambdaCrypts_BoneFiend_Animations,
	EntityResources::Enemies_LambdaCrypts_BoneFiend_Emblem,
	Size(224.0f, 278.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = BoneFiend::getHexusOpponentData();
}

BoneFiend::~BoneFiend()
{
}

Vec2 BoneFiend::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* BoneFiend::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_LambdaCrypts_BoneFiend::create();
}

HexusOpponentData* BoneFiend::getHexusOpponentData()
{
	if (BoneFiend::HexusOpponentDataInstance == nullptr)
	{
		BoneFiend::HexusOpponentDataInstance = new HexusOpponentData(
			nullptr,
			HexusResources::Menus_HexusFrameLambdaCrypts,
			Vec2(-32.0f, -112.0f),
			BoneFiend::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Shadow,
			HexusOpponentData::generateDeck(32, 0.333f,
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

	return BoneFiend::HexusOpponentDataInstance;
}