#include "MechanicalFlailClippy.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Dialogue/SpeechBubble.h"
#include "Engine/Localization/LocalizedString.h"
#include "Engine/Sound/Sound.h"

#include "Resources/EntityResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Hacking/ClippyHelp/MechanicalFlailMov.h"
#include "Strings/Hacking/RegisterEax.h"
#include "Strings/Hacking/RegisterRax.h"

using namespace cocos2d;

MechanicalFlailClippy* MechanicalFlailClippy::create()
{
	MechanicalFlailClippy* instance = new MechanicalFlailClippy();

	instance->autorelease();

	return instance;
}

MechanicalFlailClippy::MechanicalFlailClippy() : super()
{
	this->clippyAnimations = SmartAnimationNode::create(EntityResources::Misc_DaemonsHallow_FlyBot_Animations);
	this->droidChatterSound = Sound::create(SoundResources::Platformer_Entities_Droid_DroidChatter);

	this->clippyAnimations->setFlippedX(true);

	this->animationNode->addChild(this->clippyAnimations);
	this->addChild(this->droidChatterSound);
}

MechanicalFlailClippy::~MechanicalFlailClippy()
{
}

Clippy* MechanicalFlailClippy::clone()
{
	return MechanicalFlailClippy::create();
}

void MechanicalFlailClippy::onEnterTransitionDidFinish()
{
	super::onEnterTransitionDidFinish();

	LocalizedString* localizedString = Strings::Hacking_ClippyHelp_MechanicalFlailMov::create();

	if (sizeof(void*) == 8)
	{
		localizedString->setStringReplacementVariables(Strings::Hacking_RegisterRax::create());
	}
	else
	{
		localizedString->setStringReplacementVariables(Strings::Hacking_RegisterEax::create());
	}

	this->speechBubble->runDialogue(localizedString);
	this->droidChatterSound->play();
}
