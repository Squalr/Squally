#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class Buff;
class PlatformerEntity;

class EntityBuffBehavior : public AttachedBehavior
{
public:
	static EntityBuffBehavior* create(GameObject* owner);

	void applyBuff(Buff* buff);

	static const std::string MapKeyAttachedBehavior;

protected:
	EntityBuffBehavior(GameObject* owner);
	~EntityBuffBehavior();

	void onLoad() override;

private:
	typedef AttachedBehavior super;

	PlatformerEntity* entity;
};
