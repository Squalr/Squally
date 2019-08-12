#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class PlatformerEntity;

class EntityManaBehavior : public AttachedBehavior
{
public:
	static EntityManaBehavior* create(GameObject* owner, std::string attachedBehaviorArgs);

	int getMana();
	void addMana(int manaDelta);
	void setMana(int mana);
	int getMaxMana();

protected:
	EntityManaBehavior(GameObject* owner, std::string attachedBehaviorArgs);
	~EntityManaBehavior();

	void onLoad() override;

	PlatformerEntity* entity;

private:
	typedef AttachedBehavior super;

	void onRevive();
};
