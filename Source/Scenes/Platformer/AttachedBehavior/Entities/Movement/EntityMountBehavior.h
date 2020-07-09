#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class MountBase;
class PlatformerEntity;

class EntityMountBehavior : public AttachedBehavior
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
	typedef AttachedBehavior super;

	MountBase* mountTarget;
	PlatformerEntity* entity;
	cocos2d::Node* originalParent;
};
