#include "ShadowBoltClippy.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Dialogue/SpeechBubble.h"
#include "Scenes/Platformer/Dialogue/Voices.h"

#include "Resources/EntityResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

ShadowBoltClippy* ShadowBoltClippy::create()
{
	ShadowBoltClippy* instance = new ShadowBoltClippy();

	instance->autorelease();

	return instance;
}

ShadowBoltClippy::ShadowBoltClippy() : super()
{
	this->clippyAnimations = SmartAnimationNode::create(EntityResources::Helpers_EndianForest_Scrappy_Animations);

	this->clippyAnimations->setFlippedX(true);

	this->animationNode->addChild(this->clippyAnimations);
}

ShadowBoltClippy::~ShadowBoltClippy()
{
}

void ShadowBoltClippy::startDialogue()
{
	this->runDialogue(Strings::Menus_Hacking_Objects_Combat_Projectiles_ShadowBolt_ApplySpeed_ShadowBoltClippy::create()
		->setStringReplacementVariables(Strings::Menus_Hacking_Objects_Combat_Projectiles_ShadowBolt_ApplySpeed_StopShadowBolt::create()),
		Voices::GetNextVoiceMedium(Voices::VoiceType::Droid)
	);
}
