#include "LesserStrengthClippy.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Dialogue/SpeechBubble.h"

#include "Resources/EntityResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

LesserStrengthClippy* LesserStrengthClippy::create()
{
	LesserStrengthClippy* instance = new LesserStrengthClippy();

	instance->autorelease();

	return instance;
}

LesserStrengthClippy::LesserStrengthClippy() : super()
{
	this->clippyAnimations = SmartAnimationNode::create(EntityResources::Helpers_EndianForest_Scrappy_Animations);

	this->clippyAnimations->setFlippedX(true);

	this->animationNode->addChild(this->clippyAnimations);
}

LesserStrengthClippy::~LesserStrengthClippy()
{
}

Clippy* LesserStrengthClippy::innerClone()
{
	return LesserStrengthClippy::create();
}

void LesserStrengthClippy::startDialogue()
{
	this->runDialogue(
		Strings::Menus_Hacking_Abilities_LesserStrength_LesserStrengthClippy::create()
			->setStringReplacementVariables(Strings::Menus_Hacking_Abilities_LesserStrength_ReduceLesserStrength::create()),
		SoundResources::Platformer_Entities_Droid_DroidChatter
	);
}
