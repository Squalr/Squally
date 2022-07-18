#pragma once

#include "Objects/Platformer/Interactables/Mounts/MountBase.h"

class CollisionObject;
class SmartAnimationNode;

class Train : public MountBase
{
public:
	static Train* create(cocos2d::ValueMap& properties);

	void mount(PlatformerEntity* interactingEntity) override;
	void dismount() override;

	static const std::string MapKey;

protected:
	Train(cocos2d::ValueMap& properties);
	virtual ~Train();

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
	SmartAnimationNode* trainHead = nullptr;

	static const std::string PropertyColor;
};
