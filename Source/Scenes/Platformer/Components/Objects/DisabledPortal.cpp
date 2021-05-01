#include "DisabledPortal.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Objects/Platformer/Interactables/Doors/Portal.h"

using namespace cocos2d;

const std::string DisabledPortal::MapKey = "disabled-portal";

DisabledPortal* DisabledPortal::create(GameObject* owner)
{
	DisabledPortal* instance = new DisabledPortal(owner);

	instance->autorelease();

	return instance;
}

DisabledPortal::DisabledPortal(GameObject* owner) : super(owner)
{
	this->portal = dynamic_cast<Portal*>(owner);

	if (this->portal == nullptr)
	{
		this->invalidate();
	}
}

DisabledPortal::~DisabledPortal()
{
}

void DisabledPortal::onLoad()
{
	this->portal->disable();
}

void DisabledPortal::enablePortal()
{
	this->portal->enable();
}

void DisabledPortal::onDisable()
{
	super::onDisable();
	
	if (this->portal != nullptr)
	{
		this->portal->enable();
	}
}
