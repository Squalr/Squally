#include "SiphonLifeClippy.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Dialogue/SpeechBubble.h"

#include "Resources/EntityResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

SiphonLifeClippy* SiphonLifeClippy::create()
{
	SiphonLifeClippy* instance = new SiphonLifeClippy();

	instance->autorelease();

	return instance;
}

SiphonLifeClippy::SiphonLifeClippy() : super()
{
	this->clippyAnimations = SmartAnimationNode::create(EntityResources::Helpers_EndianForest_Scrappy_Animations);

	this->clippyAnimations->setFlippedX(true);

	this->animationNode->addChild(this->clippyAnimations);
}

SiphonLifeClippy::~SiphonLifeClippy()
{
}

Clippy* SiphonLifeClippy::innerClone()
{
	return SiphonLifeClippy::create();
}

void SiphonLifeClippy::startDialogue()
{
	this->runDialogue(
		Strings::Menus_Hacking_Abilities_Debuffs_SiphonLife_SiphonLifeClippy::create(),
		SoundResources::Platformer_Entities_Droid_DroidChatter
	);
}
