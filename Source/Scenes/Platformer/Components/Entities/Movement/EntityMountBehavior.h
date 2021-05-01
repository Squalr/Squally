#pragma once

#include "Engine/Components/Component.h"

class MountBase;
class PlatformerEntity;

class EntityMountBehavior : public Component
{
public:
	static EntityMountBehavior* create(GameObject* owner);

	bool mount(MountBase* mountTarget);
	bool dismount();

	static const std::string MapKey;

protected:
	EntityMountBehavior(GameObject* owner);
	virtual ~EntityMountBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef Component super;

	MountBase* mountTarget;
	PlatformerEntity* entity;
	cocos2d::Node* originalParent;
};
