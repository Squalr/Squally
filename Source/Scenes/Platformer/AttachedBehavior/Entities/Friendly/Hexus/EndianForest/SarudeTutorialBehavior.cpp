#include "SarudeTutorialBehavior.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Objects/Platformer/Collectables/Cards/CardPools/CardPools.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"
#include "Scenes/Hexus/Components/Components.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"
#include "Scenes/Hexus/StateOverride.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Dialogue/EntityDialogueBehavior.h"

#include "Resources/HexusResources.h"

#include "Strings/Platformer/Quests/EndianForest/HexusGauntlet/Sarude/IAcceptYourChallenge.h"

using namespace cocos2d;

const std::string SarudeTutorialBehavior::WinLossTrackIdentifier = "sarude-tutorial";

SarudeTutorialBehavior* SarudeTutorialBehavior::create(GameObject* owner)
{
	SarudeTutorialBehavior* instance = new SarudeTutorialBehavior(owner);

	instance->autorelease();

	return instance;
}

SarudeTutorialBehavior::SarudeTutorialBehavior(GameObject* owner) : super(owner, Strings::Platformer_Quests_EndianForest_HexusGauntlet_Sarude_IAcceptYourChallenge::create())
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
}

SarudeTutorialBehavior::~SarudeTutorialBehavior()
{
}

HexusOpponentData* SarudeTutorialBehavior::createOpponentData()
{
    return HexusOpponentData::create( 
        // TODO: This needs to work similar to the dialogue boxes, and pass the entity to a builder that accounts for scale/offsets
        this->entity->getAnimations()->getAnimationResource(),
        HexusResources::Menus_HexusFrameCastleValgrind,
        1.0f,
        Vec2(-32.0f, -64.0f),
        Vec2(-48.0f, -144.0f),
        Vec2(0.0f, -48.0f),
        SarudeTutorialBehavior::WinLossTrackIdentifier,
        HexusOpponentData::Strategy::Random,
        Card::CardStyle::Light,
        0.07f,
        HexusOpponentData::generateDeck(25, 0.07f,
        {
        }),
		CardPoolTutorial::create(),
        [=](HexusOpponentData::Result result)
        {
			switch(result)
			{
				case HexusOpponentData::Result::Win:
				default:
				{
                	this->onWin();
					break;
				}
				case HexusOpponentData::Result::Loss:
				{
                	this->onLoss();
					break;
				}
				case HexusOpponentData::Result::Draw:
				{
                	this->onDraw();
					break;
				}
			}
        }
	);
}
