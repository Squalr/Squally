#include "JumpEffect.h"

#include "Engine/Utils/GameUtils.h"
#include "Resources/EntityResources.h"

using namespace cocos2d;

JumpEffect* JumpEffect::create()
{
	JumpEffect* instance = new JumpEffect();

	instance->autorelease();

	return instance;
}

JumpEffect::JumpEffect()
{
	std::vector<std::string> animationFiles = GameUtils::getAllAnimationFiles(EntityResources::Squally_Jump_Jump_00);
}

JumpEffect::~JumpEffect()
{
}
