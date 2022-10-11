#pragma once

#include "Engine/Components/GameComponent.h"

class MountBase;
class PlatformerEntity;

class EntityMountBehavior : public GameComponent
{
public:
	static EntityMountBehavior* create(GameObject* owner);

	bool mount(MountBase* mountTarget);
	bool dismount();
	bool isMounted() const;

	static const std::string MapKey;

protected:
	EntityMountBehavior(GameObject* owner);
	virtual ~EntityMountBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef GameComponent super;

	MountBase* mountTarget = nullptr;
	PlatformerEntity* entity = nullptr;
	cocos2d::Node* originalParent = nullptr;
};
