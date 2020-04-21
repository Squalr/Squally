#include "StrengthClippy.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Dialogue/SpeechBubble.h"

#include "Resources/EntityResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

StrengthClippy* StrengthClippy::create()
{
	StrengthClippy* instance = new StrengthClippy();

	instance->autorelease();

	return instance;
}

StrengthClippy::StrengthClippy() : super()
{
	this->clippyAnimations = SmartAnimationNode::create(EntityResources::Helpers_EndianForest_Scrappy_Animations);

	this->clippyAnimations->setFlippedX(true);

	this->animationNode->addChild(this->clippyAnimations);
}

StrengthClippy::~StrengthClippy()
{
}

void StrengthClippy::startDialogue()
{
	this->runDialogue(
		Strings::Menus_Hacking_Abilities_Buffs_Strength_StrengthClippy::create(),
		SoundResources::Platformer_Entities_Droid_DroidChatter
	);
}
