#include "HexusBehaviorBase.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Dialogue/DialogueOption.h"
#include "Engine/Dialogue/SpeechBubble.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Inventory/Inventory.h"
#include "Engine/Inventory/Item.h"
#include "Engine/Inventory/MinMaxPool.h"
#include "Engine/Particles/SmartParticles.h"
#include "Engine/Save/SaveManager.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Events/HexusEvents.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Platformer/ItemPools/ErrorPool.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Dialogue/EntityDialogueBehavior.h"
#include "Scenes/Platformer/Dialogue/DialogueSet.h"
#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/EntityResources.h"
#include "Resources/ItemResources.h"
#include "Resources/ParticleResources.h"
#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

HexusBehaviorBase::HexusBehaviorBase(GameObject* owner, std::string voiceResource, bool showParticles, LocalizedString* dialogueChoiceOverride) : super(owner)
{
	this->showParticles = showParticles;
	this->winCallbacks = std::vector<std::function<void()>>();
	this->lossCallbacks = std::vector<std::function<void()>>();
	this->drawCallbacks = std::vector<std::function<void()>>();
	this->dialogueStringNode = Node::create();
	this->iconNode = Node::create();
	this->iconContainer = Node::create();
	this->cardGlow = Sprite::create(UIResources::HUD_EmblemGlow);
	this->cardSprite = Sprite::create(ItemResources::Collectables_Cards_CardSpecial);
	this->hackParticles1 = this->showParticles ? SmartParticles::create(ParticleResources::Platformer_Hacking_HackerRainOrange1, SmartParticles::CullInfo(Size(128.0f, 128.0f))) : nullptr;
	this->hackParticles2 = this->showParticles ? SmartParticles::create(ParticleResources::Platformer_Hacking_HackerRainOrange2, SmartParticles::CullInfo(Size(128.0f, 128.0f))) : nullptr;
	this->hackParticles3 = this->showParticles ? SmartParticles::create(ParticleResources::Platformer_Hacking_HackerRainOrange3, SmartParticles::CullInfo(Size(128.0f, 128.0f))) : nullptr;
	this->hackParticles4 = this->showParticles ? SmartParticles::create(ParticleResources::Platformer_Hacking_HackerRainOrange4, SmartParticles::CullInfo(Size(128.0f, 128.0f))) : nullptr;
	this->hackParticles5 = this->showParticles ? SmartParticles::create(ParticleResources::Platformer_Hacking_HackerRainOrange5, SmartParticles::CullInfo(Size(128.0f, 128.0f))) : nullptr;

	this->entity = dynamic_cast<PlatformerEntity*>(owner);
	this->dialogueChoiceOverride = dialogueChoiceOverride;
	this->voiceResource = voiceResource;
	this->rewardPool = nullptr;

	if (this->entity == nullptr)
	{
		this->invalidate();
	}

	if (this->dialogueChoiceOverride != nullptr)
	{
		this->addChild(this->dialogueChoiceOverride);
	}

	this->iconContainer->addChild(this->cardGlow);
	this->iconContainer->addChild(this->cardSprite);
	this->iconNode->addChild(this->iconContainer);
	this->addChild(this->dialogueStringNode);
	this->addChild(this->iconNode);

	if (this->showParticles)
	{
		this->addChild(this->hackParticles1);
		this->addChild(this->hackParticles2);
		this->addChild(this->hackParticles3);
		this->addChild(this->hackParticles4);
		this->addChild(this->hackParticles5);	
	}
}

HexusBehaviorBase::~HexusBehaviorBase()
{
}

void HexusBehaviorBase::onEnter()
{
	super::onEnter();

	if (this->showParticles)
	{
		this->hackParticles1->start();
		this->hackParticles2->start();
		this->hackParticles3->start();
		this->hackParticles4->start();
		this->hackParticles5->start();

		this->hackParticles2->accelerate(1.0f);
		this->hackParticles4->accelerate(1.0f);
	}

	if (this->getWins() > 0)
	{
		this->iconContainer->setVisible(false);
	}
	else
	{
		ObjectEvents::TriggerBindObjectToUI(ObjectEvents::RelocateObjectArgs(this->iconNode));
		
		this->iconContainer->runAction(RepeatForever::create(Sequence::create(
			EaseSineInOut::create(MoveTo::create(2.0f, Vec2(0.0f, -16.0f))),
			EaseSineInOut::create(MoveTo::create(2.0f, Vec2(0.0f, 0.0f))),
			nullptr
		)));
	}
}

void HexusBehaviorBase::initializePositions()
{
	super::initializePositions();

	Vec2 entityCenter = this->entity->getEntityCenterPoint();

	if (this->showParticles)
	{
		this->hackParticles1->setPosition(entityCenter);
		this->hackParticles2->setPosition(entityCenter);
		this->hackParticles3->setPosition(entityCenter);
		this->hackParticles4->setPosition(entityCenter);
		this->hackParticles5->setPosition(entityCenter);
	}

	if (this->entity != nullptr)
	{
		Vec2 offset = this->entity->getCollisionOffset() + Vec2(0.0f, this->entity->getEntitySize().height + this->entity->getHoverHeight() / 2.0f + 96.0f);

		this->iconNode->setPosition(offset);
	}
}

int HexusBehaviorBase::getWins()
{
	return SaveManager::getProfileDataOrDefault("HEXUS_WINS_" + this->getWinLossSaveKey(), Value(0)).asInt();
}

int HexusBehaviorBase::getLosses()
{
	return SaveManager::getProfileDataOrDefault("HEXUS_LOSSES_" + this->getWinLossSaveKey(), Value(0)).asInt();
}

int HexusBehaviorBase::getDraws()
{
	return SaveManager::getProfileDataOrDefault("HEXUS_DRAWS_" + this->getWinLossSaveKey(), Value(0)).asInt();
}

void HexusBehaviorBase::addWin()
{
	int wins = this->getWins() + 1;

	if (wins == 1)
	{
		this->giveItems();
	}

	this->iconContainer->setVisible(false);

	SaveManager::SaveProfileData("HEXUS_WINS_" + this->getWinLossSaveKey(), Value(wins));
}

void HexusBehaviorBase::addLoss()
{
	SaveManager::SaveProfileData("HEXUS_LOSSES_" + this->getWinLossSaveKey(), Value(this->getLosses() + 1));
}

void HexusBehaviorBase::addDraw()
{
	SaveManager::SaveProfileData("HEXUS_DRAWS_" + this->getWinLossSaveKey(), Value(this->getDraws() + 1));
}

void HexusBehaviorBase::registerWinCallback(std::function<void()> winCallback)
{
	this->winCallbacks.push_back(winCallback);
}

void HexusBehaviorBase::registerLossCallback(std::function<void()> lossCallback)
{
	this->lossCallbacks.push_back(lossCallback);
}

void HexusBehaviorBase::registerDrawCallback(std::function<void()> drawCallback)
{
	this->drawCallbacks.push_back(drawCallback);
}

void HexusBehaviorBase::onLoad()
{
	this->rewardPool = this->generateReward();
	
	if (this->rewardPool == nullptr)
	{
		this->rewardPool = ErrorPool::create();
	}

	this->addChild(this->rewardPool);

	this->entity->watchForAttachedBehavior<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
	{
		if (this->dialogueChoiceOverride != nullptr)
		{
			this->hexusOption = interactionBehavior->getMainDialogueSet()->addDialogueOption(DialogueOption::create(
				this->dialogueChoiceOverride->clone(),
				[=]()
				{
					HexusEvents::TriggerOpenHexus(HexusEvents::HexusOpenArgs(this->createOpponentData()));
				}),
				0.5f
			);
		}
		else
		{
			if (this->getWins() <= 0)
			{
				this->hexusOption = interactionBehavior->getMainDialogueSet()->addDialogueOption(DialogueOption::create(
					Strings::Platformer_Dialogue_Hexus_HowAboutARoundOfHexus::create()->setStringReplacementVariables(Strings::Hexus_Hexus::create()),
					[=]()
					{
						HexusEvents::TriggerOpenHexus(HexusEvents::HexusOpenArgs(this->createOpponentData()));
					}),
					0.5f
				);
			}
			else
			{
				this->hexusOption = interactionBehavior->getMainDialogueSet()->addDialogueOption(DialogueOption::create(
					Strings::Platformer_Dialogue_Hexus_HowAboutARematch::create()->setStringReplacementVariables(Strings::Hexus_Hexus::create()),
					[=]()
					{
						HexusEvents::TriggerOpenHexus(HexusEvents::HexusOpenArgs(this->createOpponentData()));
					}),
					0.5f
				);
			}
		}
	});
}

void HexusBehaviorBase::onDisable()
{
	super::onDisable();
}

void HexusBehaviorBase::giveItems()
{
	if (this->rewardPool != nullptr)
	{
		PlatformerEvents::TriggerGiveItemsFromPool(PlatformerEvents::GiveItemsFromPoolArgs(this->rewardPool, Strings::Platformer_Notifications_ItemWon::create()));
	}
}

void HexusBehaviorBase::removeFromDialogue()
{
	this->entity->watchForAttachedBehavior<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
	{
		interactionBehavior->getMainDialogueSet()->removeDialogueOption(this->hexusOption);
	});
}

void HexusBehaviorBase::onWin()
{
	static int DialogueOptionCount = 2;
	static int DialogueIndex = RandomHelper::random_int(0, DialogueOptionCount);

	this->iconNode->setVisible(false);

	switch (DialogueIndex++ % DialogueOptionCount)
	{
		default:
		case 0:
		{
			this->runPostMatchDialogue(Strings::Platformer_Dialogue_Hexus_WellPlayed::create());
			break;
		}
		case 1:
		{
			this->runPostMatchDialogue(Strings::Platformer_Dialogue_Hexus_GoodGame::create());
			break;
		}
	}

	this->addWin();

	for (auto callback : this->winCallbacks)
	{
		callback();
	}
}

void HexusBehaviorBase::onLoss()
{
	static int DialogueOptionCount = 1;
	static int DialogueIndex = RandomHelper::random_int(0, DialogueOptionCount);

	switch (DialogueIndex++ % DialogueOptionCount)
	{
		default:
		case 0:
		{
			this->runPostMatchDialogue(Strings::Platformer_Dialogue_Hexus_BetterLuckNextTime::create());
			break;
		}
	}

	this->addLoss();

	for (auto callback : this->lossCallbacks)
	{
		callback();
	}
}

void HexusBehaviorBase::onDraw()
{
	static int DialogueOptionCount = 1;
	static int DialogueIndex = RandomHelper::random_int(0, DialogueOptionCount);

	switch (DialogueIndex++ % DialogueOptionCount)
	{
		default:
		case 0:
		{
			this->runPostMatchDialogue(Strings::Platformer_Dialogue_Hexus_ADraw::create());
			break;
		}
	}

	this->addDraw();

	for (auto callback : this->drawCallbacks)
	{
		callback();
	}
}

void HexusBehaviorBase::runPostMatchDialogue(LocalizedString* dialogue)
{
	// Add it to retain it until the end of this object's life
	this->dialogueStringNode->addChild(dialogue);

	this->runAction(Sequence::create(
		DelayTime::create(0.5f),
		CallFunc::create([=]()
		{
			this->entity->getAttachedBehavior<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
			{
				interactionBehavior->getSpeechBubble()->runDialogue(dialogue->clone(), this->voiceResource);
			});
		}),
		nullptr
	));
}

HexusOpponentData* HexusBehaviorBase::createOpponentData()
{
    return HexusOpponentData::create( 
		HexusEvents::BuildPreviewNode(this->entity),
        this->getBackgroundResource(),
        this->entity->getDialogueOffset() + this->getAvatarOffset(),
        this->getWinLossSaveKey(),
        HexusOpponentData::Strategy::Random,
        Card::CardStyle::Light,
        this->generateDeck(),
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
        },
		this->getStateOverride(),
		this->getTutorials()
	);
}

std::vector<TutorialBase*> HexusBehaviorBase::getTutorials()
{
	return { };
}

Vec2 HexusBehaviorBase::getAvatarOffset()
{
	// A pretty good default
	return Vec2(-16.0f, -32.0f);
}
