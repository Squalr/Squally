#pragma once

#include "Engine/Components/Component.h"

class ComponentGroup : public Component
{
public:

protected:
	ComponentGroup(GameObject* owner, std::vector<Component*> component);
	virtual ~ComponentGroup();

private:
	typedef Component super;
};

