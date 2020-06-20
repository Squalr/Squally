#include "BlindClippy.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Dialogue/SpeechBubble.h"
#include "Scenes/Platformer/Dialogue/Voices.h"

#include "Resources/EntityResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

BlindClippy* BlindClippy::create()
{
	BlindClippy* instance = new BlindClippy();

	instance->autorelease();

	return instance;
}

BlindClippy::BlindClippy() : super()
{
	this->clippyAnimations = SmartAnimationNode::create(EntityResources::Helpers_EndianForest_Scrappy_Animations);

	this->clippyAnimations->setFlippedX(true);

	this->animationNode->addChild(this->clippyAnimations);
}

BlindClippy::~BlindClippy()
{
}

void BlindClippy::startDialogue()
{
	this->runDialogue(
		Strings::Menus_Hacking_Abilities_Debuffs_Blind_BlindClippy::create()
			->setStringReplacementVariables(Strings::Menus_Hacking_Abilities_Debuffs_Blind_ReduceBlind::create()),
		Voices::GetNextVoiceMedium(Voices::VoiceType::Droid)
	);
}
