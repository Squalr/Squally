#include "TrainingHealClippy.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Dialogue/SpeechBubble.h"

#include "Resources/EntityResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

TrainingHealClippy* TrainingHealClippy::create()
{
	TrainingHealClippy* instance = new TrainingHealClippy();

	instance->autorelease();

	return instance;
}

TrainingHealClippy::TrainingHealClippy() : super()
{
	this->clippyAnimations = SmartAnimationNode::create(EntityResources::Helpers_EndianForest_Scrappy_Animations);

	this->clippyAnimations->setFlippedX(true);

	this->animationNode->addChild(this->clippyAnimations);
}

TrainingHealClippy::~TrainingHealClippy()
{
}

void TrainingHealClippy::startDialogue()
{
	this->runDialogue(Strings::Menus_Hacking_ClippyHelp_Abilities_TrainingHeal_TrainingHealAdd::create(), SoundResources::Platformer_Entities_Droid_DroidChatter);
}
