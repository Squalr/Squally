#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class Buff;
class PlatformerEntity;

class EntityBuffBehavior : public AttachedBehavior
{
public:
	static EntityBuffBehavior* create(GameObject* owner);

	void applyBuff(Buff* buff);
	void removeBuff(Buff* buff);
	void removeBuffsById(std::string buffId);

	static const std::string MapKeyAttachedBehavior;

protected:
	EntityBuffBehavior(GameObject* owner);
	virtual ~EntityBuffBehavior();

	void onLoad() override;

private:
	typedef AttachedBehavior super;

	PlatformerEntity* entity;

	std::vector<Buff*> buffs;
};
