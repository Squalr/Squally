#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

namespace cocos2d
{
	class Sprite;
}

class ClickableNode;
class PlatformerEntity;

class EntityEqBehaviorBase : public AttachedBehavior
{
public:
	void setEq(int eq);
	int getEq();
	bool setEqExperience(int eqExperience);
	bool addEqExperience(int eqExperience);
	int getEqExperience();
	
	static const int DefaultEq;

protected:
	EntityEqBehaviorBase(GameObject* owner, std::string attachedBehaviorArgs);
	~EntityEqBehaviorBase();

	void onLoad() override;

	PlatformerEntity* entity;

private:
	typedef AttachedBehavior super;
	
	int eq;
	int eqExperience;
};
