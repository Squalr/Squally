#pragma once

#include "Objects/Platformer/Interactables/Mounts/MountBase.h"

namespace cocos2d
{
	class Sprite;
}

class MineCart : public MountBase
{
public:
	static MineCart* create(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getReparentPosition() override;

	static const std::string MapKey;

protected:
	MineCart(cocos2d::ValueMap& properties);
	virtual ~MineCart();

	void onEnter() override;
	void initializePositions() override;
	void update(float dt) override;
	void mount(PlatformerEntity* interactingEntity) override;
	void dismount() override;

private:
	typedef MountBase super;
	
	enum class CartColor
	{
		Brown,
		Blue
	};
	
	enum class CartDirection
	{
		Left,
		Right
	};

	void moveCart(float dt);
	void parseColor();
	void parseDirection();

	bool isMoving;
	CartColor cartColor;
	CartDirection cartDirection;
	cocos2d::Sprite* body;
	cocos2d::Sprite* wheelFront;
	cocos2d::Sprite* wheelBack;

	static const std::string PropertyColor;
	static const std::string PropertyDirection;
};
