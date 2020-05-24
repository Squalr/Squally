#include "SiphonLifeClippy.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Dialogue/SpeechBubble.h"
#include "Scenes/Platformer/Dialogue/Voices.h"

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

void SiphonLifeClippy::startDialogue()
{
	this->runDialogue(
		Strings::Menus_Hacking_Abilities_Debuffs_SiphonLife_SiphonLifeClippy::create(),
		Voices::GetNextVoiceMedium(Voices::VoiceType::Droid)
	);
}
