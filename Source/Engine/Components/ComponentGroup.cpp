#include "ComponentGroup.h"

#include "Engine/Maps/GameObject.h"

using namespace cocos2d;

ComponentGroup::ComponentGroup(GameObject* owner, std::vector<Component*> component) : super(owner)
{
	for (auto next : component)
	{
		owner->attachBehavior(next);
	}
}

ComponentGroup::~ComponentGroup()
{
}
