#include "EnableAllClippyBehavior.h"

#include "Engine/Hackables/HackableObject.h"

using namespace cocos2d;

const std::string EnableAllClippyBehavior::MapKeyAttachedBehavior = "enable-all-clippy";

EnableAllClippyBehavior* EnableAllClippyBehavior::create(GameObject* owner)
{
	EnableAllClippyBehavior* instance = new EnableAllClippyBehavior(owner);

	instance->autorelease();

	return instance;
}

EnableAllClippyBehavior::EnableAllClippyBehavior(GameObject* owner) : super(owner)
{
	this->hackableObject = dynamic_cast<HackableObject*>(owner);

	if (this->hackableObject == nullptr)
	{
		this->invalidate();
	}
}

EnableAllClippyBehavior::~EnableAllClippyBehavior()
{
}

void EnableAllClippyBehavior::onLoad()
{
	this->hackableObject->enableAllClippy();
}
