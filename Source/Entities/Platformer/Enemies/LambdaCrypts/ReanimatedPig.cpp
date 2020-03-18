#include "ReanimatedPig.h"

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

const std::string ReanimatedPig::MapKeyReanimatedPig = "reanimated-pig";
HexusOpponentData* ReanimatedPig::HexusOpponentDataInstance = nullptr;
const std::string ReanimatedPig::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_REANIMATED_PIG";

ReanimatedPig* ReanimatedPig::deserialize(ValueMap& properties)
{
	ReanimatedPig* instance = new ReanimatedPig(properties);

	instance->autorelease();

	return instance;
}

ReanimatedPig::ReanimatedPig(ValueMap& properties) : super(properties,
	ReanimatedPig::MapKeyReanimatedPig,
	EntityResources::Enemies_LambdaCrypts_ReanimatedPig_Animations,
	EntityResources::Enemies_LambdaCrypts_ReanimatedPig_Emblem,
	Size(256.0f, 240.0f),
	0.8f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = ReanimatedPig::getHexusOpponentData();
}

ReanimatedPig::~ReanimatedPig()
{
}

Vec2 ReanimatedPig::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* ReanimatedPig::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_LambdaCrypts_ReanimatedPig::create();
}

HexusOpponentData* ReanimatedPig::getHexusOpponentData()
{
	if (ReanimatedPig::HexusOpponentDataInstance == nullptr)
	{
		ReanimatedPig::HexusOpponentDataInstance = new HexusOpponentData(
			nullptr,
			HexusResources::Menus_HexusFrameLambdaCrypts,
			Vec2(-32.0f, -112.0f),
			ReanimatedPig::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Shadow,
			HexusOpponentData::generateDeck(32, 0.083f,
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

	return ReanimatedPig::HexusOpponentDataInstance;
}