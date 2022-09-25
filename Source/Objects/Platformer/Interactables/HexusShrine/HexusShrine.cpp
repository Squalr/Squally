#include "HexusShrine.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Events/NavigationEvents.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Particles/SmartParticles.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Events/DialogueEvents.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Platformer/ItemPools/RecipePools/RecipePoolDeserializer.h"
#include "Scenes/Platformer/Components/Entities/Dialogue/EntityDialogueBehavior.h"
#include "Scenes/Platformer/Components/Entities/Friendly/Hexus/HexusBehaviorBase.h"

#include "Resources/ObjectResources.h"
#include "Resources/ParticleResources.h"
#include "Resources/MapResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string HexusShrine::MapKey = "hexus-shrine";
const std::string HexusShrine::PropertyEntityTag = "entity-tag";

HexusShrine* HexusShrine::create(ValueMap& properties)
{
	HexusShrine* instance = new HexusShrine(properties);

	instance->autorelease();

	return instance;
}

HexusShrine::HexusShrine(ValueMap& properties) : super(properties, InteractObject::InteractType::Input, CSize(112.0f, 148.0f))
{
	this->shrine = Sprite::create(ObjectResources::Interactive_HexusShrine_Shrine);
	this->iconNode = Node::create();
	this->undefeatedContainer = Node::create();
	this->defeatedContainer = Node::create();
	this->hackParticles1 = SmartParticles::create(ParticleResources::Platformer_Hacking_HackerRainOrange1, SmartParticles::CullInfo(CSize(128.0f, 128.0f)));
	this->hackParticles2 = SmartParticles::create(ParticleResources::Platformer_Hacking_HackerRainOrange2, SmartParticles::CullInfo(CSize(128.0f, 128.0f)));
	this->hackParticles3 = SmartParticles::create(ParticleResources::Platformer_Hacking_HackerRainOrange3, SmartParticles::CullInfo(CSize(128.0f, 128.0f)));
	this->hackParticles4 = SmartParticles::create(ParticleResources::Platformer_Hacking_HackerRainOrange4, SmartParticles::CullInfo(CSize(128.0f, 128.0f)));
	this->hackParticles5 = SmartParticles::create(ParticleResources::Platformer_Hacking_HackerRainOrange5, SmartParticles::CullInfo(CSize(128.0f, 128.0f)));
	this->entityTag = GameUtils::getKeyOrDefault(this->properties, HexusShrine::PropertyEntityTag, Value("")).asString();
	Sprite* cardGlow = Sprite::create(UIResources::HUD_EmblemGlow);
	Sprite* overheadSprite = Sprite::create(ObjectResources::Interactive_HexusShrine_Jigsaw);
	Sprite* overheadSpriteDefeated = Sprite::create(ObjectResources::Interactive_HexusShrine_JigsawCompleted);

	this->undefeatedContainer->addChild(cardGlow);
	this->undefeatedContainer->addChild(overheadSprite);
	this->defeatedContainer->addChild(overheadSpriteDefeated);
	this->iconNode->addChild(this->undefeatedContainer);
	this->iconNode->addChild(this->defeatedContainer);
	this->addChild(this->shrine);
	this->addChild(this->iconNode);
	this->addChild(this->hackParticles1);
	this->addChild(this->hackParticles2);
	this->addChild(this->hackParticles3);
	this->addChild(this->hackParticles4);
	this->addChild(this->hackParticles5);	
}

HexusShrine::~HexusShrine()
{
}

void HexusShrine::onEnter()
{
	super::onEnter();

	this->hackParticles1->start();
	this->hackParticles2->start();
	this->hackParticles3->start();
	this->hackParticles4->start();
	this->hackParticles5->start();

	this->hackParticles2->accelerate(1.0f);
	this->hackParticles4->accelerate(1.0f);

	ObjectEvents::WatchForObject<PlatformerEntity>(this, [=](PlatformerEntity* entity)
	{
		this->entity = entity;
		this->entity->watchForComponent<HexusBehaviorBase>([=](HexusBehaviorBase* hexusBehavior)
		{
			bool wasDefeated = hexusBehavior->getWins() > 0;
			this->undefeatedContainer->setVisible(!wasDefeated);
			this->defeatedContainer->setVisible(wasDefeated);
		});
	}, this->entityTag);

	ObjectEvents::TriggerBindObjectToUI(RelocateObjectArgs(this->iconNode));
	
	this->defeatedContainer->runAction(RepeatForever::create(Sequence::create(
		EaseSineInOut::create(MoveTo::create(2.0f, Vec2(0.0f, -16.0f))),
		EaseSineInOut::create(MoveTo::create(2.0f, Vec2(0.0f, 0.0f))),
		nullptr
	)));
	this->undefeatedContainer->runAction(RepeatForever::create(Sequence::create(
		EaseSineInOut::create(MoveTo::create(2.0f, Vec2(0.0f, -16.0f))),
		EaseSineInOut::create(MoveTo::create(2.0f, Vec2(0.0f, 0.0f))),
		nullptr
	)));
}

void HexusShrine::initializePositions()
{
	super::initializePositions();
	
	this->shrine->setPosition(Vec2(0.0f, 0.0f));
	this->iconNode->setPosition(Vec2(0.0f, 192.0f));
	
	const Vec2 particlePosition = Vec2(0.0f, 96.0f);
	this->hackParticles1->setPosition(particlePosition);
	this->hackParticles2->setPosition(particlePosition);
	this->hackParticles3->setPosition(particlePosition);
	this->hackParticles4->setPosition(particlePosition);
	this->hackParticles5->setPosition(particlePosition);
}

void HexusShrine::onInteract(PlatformerEntity* interactingEntity)
{
	super::onInteract(interactingEntity);

	if (this->entity != nullptr)
	{
		this->entity->getComponent<EntityDialogueBehavior>([=](EntityDialogueBehavior* dialogueBehavior)
		{
			dialogueBehavior->progressDialogue();
		});
	}
}
