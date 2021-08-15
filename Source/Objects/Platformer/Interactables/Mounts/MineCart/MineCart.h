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

	float cartSpeed = 0.0f;
	bool canMoveHack = true;
	bool isMoving = false;
	CartColor cartColor = CartColor::Brown;
	CartDirection cartDirection = CartDirection::Left;
	CollisionObject* bottomCollision = nullptr;
	cocos2d::Sprite* body = nullptr;
	cocos2d::Sprite* wheelFront = nullptr;
	cocos2d::Sprite* wheelBack = nullptr;

	static const std::string PropertyColor;
	static const std::string PropertyDirection;
	static const std::string PropertySpeed;
};
