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
	void removeAllBuffs();

	static const std::string MapKeyAttachedBehavior;

protected:
	EntityBuffBehavior(GameObject* owner);
	virtual ~EntityBuffBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef AttachedBehavior super;

	cocos2d::Node* buffNode;
	
	PlatformerEntity* entity;

	std::vector<Buff*> buffs;
};
