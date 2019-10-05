#include "TutorialBHexusBehavior.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"
#include "Scenes/Hexus/Components/Components.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"
#include "Scenes/Hexus/StateOverride.h"

#include "Resources/EntityResources.h"
#include "Resources/HexusResources.h"

using namespace cocos2d;

const std::string TutorialBHexusBehavior::MapKeyAttachedBehavior = "hexus-tutorial-B";

TutorialBHexusBehavior* TutorialBHexusBehavior::create(GameObject* owner)
{
	TutorialBHexusBehavior* instance = new TutorialBHexusBehavior(owner);

	instance->autorelease();

	return instance;
}

TutorialBHexusBehavior::TutorialBHexusBehavior(GameObject* owner) : super(owner)
{
    this->entity = dynamic_cast<PlatformerEntity*>(owner);

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
}

TutorialBHexusBehavior::~TutorialBHexusBehavior()
{
}

void TutorialBHexusBehavior::onLoad()
{
    super::onLoad();
}

HexusOpponentData* TutorialBHexusBehavior::createOpponentData()
{
    return HexusOpponentData::create( 
        // TODO: This needs to work similar to the dialogue boxes, and pass the entity to a builder that accounts for scale/offsets
        this->entity->getAnimations()->getAnimationResource(),
        HexusResources::Menus_HexusFrameCastleValgrind,
        1.0f,
        Vec2(-32.0f, -64.0f),
        Vec2(-48.0f, -144.0f),
        Vec2(0.0f, -48.0f),
        "todo",
        HexusOpponentData::Strategy::Random,
        Card::CardStyle::Light,
        0.07f,
        HexusOpponentData::generateDeck(25, 0.07f,
        {
        }),
        StateOverride::create(
            // Player losses
            1,
            // Enemy losses
            0,
            // Player's turn
            true,
            // Player passed
            false,
            // Enemy passed
            false,
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
                CardList::getInstance()->cardListByName.at(CardKeys::Decimal15),
            },
            // Enemy hand
            std::vector<CardData*>
            {
                CardList::getInstance()->cardListByName.at(CardKeys::Hex7),
            },
            // Player binary cards
            std::vector<CardData*>
            {
            },
            // Player decimal cards
            std::vector<CardData*>
            {
                CardList::getInstance()->cardListByName.at(CardKeys::Decimal7),
                CardList::getInstance()->cardListByName.at(CardKeys::Decimal9),
            },
            // Player hex cards
            std::vector<CardData*>
            {
                CardList::getInstance()->cardListByName.at(CardKeys::Hex12),
            },
            // Enemy binary cards
            std::vector<CardData*>
            {
                CardList::getInstance()->cardListByName.at(CardKeys::Binary0),
                CardList::getInstance()->cardListByName.at(CardKeys::Binary8),
            },
            // Enemy decimal cards
            std::vector<CardData*>
            {
            },
            // Enemy hex cards
            std::vector<CardData*>
            {
                CardList::getInstance()->cardListByName.at(CardKeys::Hex4),
            },
            { TutorialBIntroSequence::create() })
	);
}