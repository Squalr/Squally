#include "ScrappyClippy.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Dialogue/SpeechBubble.h"

#include "Resources/EntityResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

ScrappyClippy* ScrappyClippy::create(LocalizedString* helpText)
{
	ScrappyClippy* instance = new ScrappyClippy(helpText);

	instance->autorelease();

	return instance;
}

ScrappyClippy::ScrappyClippy(LocalizedString* helpText) : super()
{
	this->clippyAnimations = SmartAnimationNode::create(EntityResources::Helpers_EndianForest_Scrappy_Animations);
	this->helpText = helpText;

	this->clippyAnimations->setFlippedX(true);

	this->animationNode->addChild(this->clippyAnimations);
	this->addChild(helpText);
}

ScrappyClippy::~ScrappyClippy()
{
}

void ScrappyClippy::startDialogue()
{
	this->runDialogue(this->helpText == nullptr ? nullptr : this->helpText->clone(), SoundResources::Platformer_Entities_Droid_DroidChatter);
}

Clippy* ScrappyClippy::innerClone()
{
	return ScrappyClippy::create(this->helpText == nullptr ? nullptr : this->helpText->clone());
}
