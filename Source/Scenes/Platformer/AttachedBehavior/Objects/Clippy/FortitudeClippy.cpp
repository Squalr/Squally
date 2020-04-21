#include "FortitudeClippy.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Dialogue/SpeechBubble.h"

#include "Resources/EntityResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

FortitudeClippy* FortitudeClippy::create()
{
	FortitudeClippy* instance = new FortitudeClippy();

	instance->autorelease();

	return instance;
}

FortitudeClippy::FortitudeClippy() : super()
{
	this->clippyAnimations = SmartAnimationNode::create(EntityResources::Helpers_EndianForest_Scrappy_Animations);

	this->clippyAnimations->setFlippedX(true);

	this->animationNode->addChild(this->clippyAnimations);
}

FortitudeClippy::~FortitudeClippy()
{
}

void FortitudeClippy::startDialogue()
{
	this->runDialogue(
		Strings::Menus_Hacking_Abilities_Buffs_Fortitude_FortitudeClippy::create(),
		SoundResources::Platformer_Entities_Droid_DroidChatter
	);
}
