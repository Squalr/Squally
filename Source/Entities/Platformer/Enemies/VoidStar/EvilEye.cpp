#include "EvilEye.h"

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

const std::string EvilEye::MapKey = "evil-eye";
HexusOpponentData* EvilEye::HexusOpponentDataInstance = nullptr;
const std::string EvilEye::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_EVIL_EYE";

EvilEye* EvilEye::deserialize(ValueMap& properties)
{
	EvilEye* instance = new EvilEye(properties);

	instance->autorelease();

	return instance;
}

EvilEye::EvilEye(ValueMap& properties) : super(properties,
	EvilEye::MapKey,
	EntityResources::Enemies_VoidStar_EvilEye_Animations,
	EntityResources::Enemies_VoidStar_EvilEye_Emblem,
	Size(720.0f, 840.0f),
	0.6f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = EvilEye::getHexusOpponentData();
}

EvilEye::~EvilEye()
{
}

Vec2 EvilEye::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* EvilEye::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_VoidStar_EvilEye::create();
}

HexusOpponentData* EvilEye::getHexusOpponentData()
{
	if (EvilEye::HexusOpponentDataInstance == nullptr)
	{
		EvilEye::HexusOpponentDataInstance = new HexusOpponentData(
			nullptr,
			HexusResources::Menus_HexusFrameVoidStar,
			Vec2(-32.0f, -112.0f),
			EvilEye::HexusSaveKey,
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

	return EvilEye::HexusOpponentDataInstance;
}