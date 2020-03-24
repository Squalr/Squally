#include "StoneSkinClippy.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Dialogue/SpeechBubble.h"

#include "Resources/EntityResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

StoneSkinClippy* StoneSkinClippy::create()
{
	StoneSkinClippy* instance = new StoneSkinClippy();

	instance->autorelease();

	return instance;
}

StoneSkinClippy::StoneSkinClippy() : super()
{
	this->clippyAnimations = SmartAnimationNode::create(EntityResources::Helpers_EndianForest_Scrappy_Animations);

	this->clippyAnimations->setFlippedX(true);

	this->animationNode->addChild(this->clippyAnimations);
}

StoneSkinClippy::~StoneSkinClippy()
{
}

Clippy* StoneSkinClippy::innerClone()
{
	return StoneSkinClippy::create();
}

void StoneSkinClippy::startDialogue()
{
	this->runDialogue(
		Strings::Menus_Hacking_Abilities_StoneSkin_StoneSkinClippy::create()
			->setStringReplacementVariables(Strings::Menus_Hacking_Abilities_StoneSkin_ReduceStoneSkin::create()),
		SoundResources::Platformer_Entities_Droid_DroidChatter
	);
}
