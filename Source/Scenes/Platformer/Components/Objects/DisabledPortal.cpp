#include "DisabledPortal.h"

#include "2d/CCActionEase.h"
#include "2d/CCActionInstant.h"
#include "2d/CCActionInterval.h"
#include "base/CCEventCustom.h"
#include "base/CCEventListenerCustom.h"
#include "base/CCValue.h"

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
