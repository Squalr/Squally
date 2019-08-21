#include "PendulumBladeClippy.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Dialogue/SpeechBubble.h"
#include "Engine/Localization/LocalizedString.h"
#include "Engine/Sound/Sound.h"

#include "Resources/EntityResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Menus/Hacking/ClippyHelp/PendulumBladeMov.h"
#include "Strings/Menus/Hacking/RegisterEax.h"
#include "Strings/Menus/Hacking/RegisterRax.h"

using namespace cocos2d;

PendulumBladeClippy* PendulumBladeClippy::create()
{
	PendulumBladeClippy* instance = new PendulumBladeClippy();

	instance->autorelease();

	return instance;
}

PendulumBladeClippy::PendulumBladeClippy() : super()
{
	this->clippyAnimations = SmartAnimationNode::create(EntityResources::Helpers_EndianForest_Scrappy_Animations);
	this->droidChatterSound = Sound::create(SoundResources::Platformer_Entities_Droid_DroidChatter);

	this->clippyAnimations->setFlippedX(true);

	this->animationNode->addChild(this->clippyAnimations);
	this->addChild(this->droidChatterSound);
}

PendulumBladeClippy::~PendulumBladeClippy()
{
}

Clippy* PendulumBladeClippy::innerClone()
{
	return PendulumBladeClippy::create();
}

void PendulumBladeClippy::onEnterTransitionDidFinish()
{
	super::onEnterTransitionDidFinish();

	LocalizedString* localizedString = Strings::Menus_Hacking_ClippyHelp_PendulumBladeMov::create();

	if (sizeof(void*) == 8)
	{
		localizedString->setStringReplacementVariables(Strings::Menus_Hacking_RegisterRax::create());
	}
	else
	{
		localizedString->setStringReplacementVariables(Strings::Menus_Hacking_RegisterEax::create());
	}

	this->speechBubble->runDialogue(localizedString);
	this->droidChatterSound->play();
}
