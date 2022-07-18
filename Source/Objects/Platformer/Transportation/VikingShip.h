#pragma once

#include "Objects/Platformer/Interactables/Mounts/MountBase.h"

class CollisionObject;
class SmartAnimationNode;

class VikingShip : public MountBase
{
public:
	static VikingShip* create(cocos2d::ValueMap& properties);

	void mount(PlatformerEntity* interactingEntity) override;
	void dismount() override;

	static const std::string MapKey;

protected:
	VikingShip(cocos2d::ValueMap& properties);
	virtual ~VikingShip();

	void onEnter() override;
	void update(float dt) override;
	void initializePositions() override;
	void initializeListeners() override;
	
	cocos2d::Vec2 getReparentPosition() override;

private:
	typedef MountBase super;
	
	enum class CartColor
	{
		Brown,
		Blue
	};

	CollisionObject* bottomCollision = nullptr;
	SmartAnimationNode* ship = nullptr;
};
