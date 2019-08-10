#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

namespace cocos2d
{
	class Sprite;
}

class ClickableNode;
class PlatformerEntity;

class EntityManaBehaviorBase : public AttachedBehavior
{
public:
	int getMana();
	void addMana(int manaDelta);
	void setMana(int mana);
	int getMaxMana();

protected:
	EntityManaBehaviorBase(GameObject* owner, std::string attachedBehaviorArgs);
	~EntityManaBehaviorBase();

	void onLoad() override;

	PlatformerEntity* entity;

private:
	typedef AttachedBehavior super;
	
	int mana;
	int maxMana;
};
