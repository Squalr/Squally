#pragma once

#include "Objects/Platformer/Interactables/Mounts/MountBase.h"

namespace cocos2d
{
	class Sprite;
}

class CollisionObject;

class MineCart : public MountBase
{
public:
	enum class CartDirection
	{
		Left,
		Right
	};

	static MineCart* create(cocos2d::ValueMap& properties);

	void mount(PlatformerEntity* interactingEntity) override;
	void dismount() override;
	void setCartDirection(CartDirection cartDirection);

	static const std::string MapKey;

protected:
	MineCart(cocos2d::ValueMap& properties);
	virtual ~MineCart();

	void onEnter() override;
	void update(float dt) override;
	void initializePositions() override;
	void initializeListeners() override;
	cocos2d::Vec2 getReparentPosition() override;
	cocos2d::Vec2 getButtonOffset() override;
	void registerHackables() override;
	HackablePreview* createDefaultPreview() override;

private:
	typedef MountBase super;
	
	enum class CartColor
	{
		Brown,
		Blue
	};

	void updateCanMove();
	void reverse();
	void faceEntityTowardsDirection();
	void moveCart(float dt);
	void parseColor();
	void parseDirection();

	float cartSpeed;
	bool canMoveHack;
	bool isMoving;
	CartColor cartColor;
	CartDirection cartDirection;
	CollisionObject* bottomCollision;
	cocos2d::Sprite* body;
	cocos2d::Sprite* wheelFront;
	cocos2d::Sprite* wheelBack;

	static const std::string PropertyColor;
	static const std::string PropertyDirection;
	static const std::string PropertySpeed;
};
