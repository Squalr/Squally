#include "PerceptronUnarmored.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Particles/SmartParticles.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Sound/WorldSound.h"
#include "Engine/Utils/GameUtils.h"
#include "Scenes/Platformer/Level/Physics/PlatformerPhysicsTypes.h"

#include "Resources/EntityResources.h"
#include "Resources/FXResources.h"
#include "Resources/ObjectResources.h"
#include "Resources/ParticleResources.h"
#include "Resources/SoundResources.h"

using namespace cocos2d;

const std::string PerceptronUnarmored::MapKey = "perceptron-unarmored";

PerceptronUnarmored* PerceptronUnarmored::create(ValueMap& properties)
{
	PerceptronUnarmored* instance = new PerceptronUnarmored(properties);

	instance->autorelease();

	return instance;
}

PerceptronUnarmored::PerceptronUnarmored(ValueMap& properties, int requiredHits) : super(properties, CSize(96.0f, 96.0f), requiredHits)
{
	this->explosion = SmartAnimationSequenceNode::create();
	this->breakSound = WorldSound::create(SoundResources::Platformer_FX_Explosions_Explosion1);
	this->perceptron = SmartAnimationNode::create(EntityResources::Enemies_VoidStar_Perceptron_Animations);

	this->perceptron->playAnimation("Idle_Unarmored", SmartAnimationNode::AnimationPlayMode::Repeat);
	this->perceptron->setScale(0.7f);
	this->perceptron->setFlippedX(true);

	this->contentNode->addChild(this->perceptron);
	this->contentNode->addChild(this->explosion);
	this->contentNode->addChild(this->breakSound);
}

PerceptronUnarmored::~PerceptronUnarmored()
{
}

void PerceptronUnarmored::initializePositions()
{
	super::initializePositions();

	this->perceptron->setPosition(Vec2(0.0f, -40.0f));
}

void PerceptronUnarmored::initializeListeners()
{
	super::initializeListeners();
}

Vec2 PerceptronUnarmored::getButtonOffset()
{
	return Vec2(0.0f, 96.0f);
}

void PerceptronUnarmored::onBreak()
{
	super::onBreak();
	
	this->perceptron->setVisible(false);
	this->explosion->playAnimation(FXResources::ExplosionNormal_Explosion_0000, 0.035f, true);
	this->breakSound->play();

	this->broadcastMapEvent("perceptron-dead", ValueMap());
}
