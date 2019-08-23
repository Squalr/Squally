#include "VoidArcher.h"

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

#include "Strings/Platformer/Entities/Names/Enemies/VoidStar/VoidArcher.h"

using namespace cocos2d;

const std::string VoidArcher::MapKeyVoidArcher = "void-archer";
HexusOpponentData* VoidArcher::HexusOpponentDataInstance = nullptr;
const std::string VoidArcher::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_VOID_ARCHER";

VoidArcher* VoidArcher::deserialize(ValueMap& properties)
{
	VoidArcher* instance = new VoidArcher(properties);

	instance->autorelease();

	return instance;
}

VoidArcher::VoidArcher(ValueMap& properties) : super(properties,
	VoidArcher::MapKeyVoidArcher,
	EntityResources::Enemies_VoidStar_VoidArcher_Animations,
	EntityResources::Enemies_VoidStar_VoidArcher_Emblem,
	Size(196.0f, 348.0f),
	0.65f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = VoidArcher::getHexusOpponentData();
}

VoidArcher::~VoidArcher()
{
}

Vec2 VoidArcher::getDialogueOffset()
{
	return Vec2(-32.0f, -112.0f);
}

LocalizedString* VoidArcher::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_VoidStar_VoidArcher::create();
}

HexusOpponentData* VoidArcher::getHexusOpponentData()
{
	if (VoidArcher::HexusOpponentDataInstance == nullptr)
	{
		VoidArcher::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Enemies_VoidStar_VoidArcher_Animations,
			HexusResources::Menus_HexusFrameVoidStar,
			0.65f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -112.0f),
			VoidArcher::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Shadow,
			0.583f,
			HexusOpponentData::generateDeck(32, 0.583f,
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

	return VoidArcher::HexusOpponentDataInstance;
}