#pragma once

#include "Objects/Platformer/Interactables/Mounts/MountBase.h"

namespace cocos2d
{
	class Sprite;
}

class CollisionObject;
class WorldSound;

class MineCart : public MountBase
{
public:
	static MineCart* create(cocos2d::ValueMap& properties);

	void mount(PlatformerEntity* interactingEntity) override;
	void dismount(PlatformerEntity* entity) override;

	static const std::string MapKey;

protected:
	MineCart(cocos2d::ValueMap& properties);
	virtual ~MineCart();

	void onEnter() override;
	void update(float dt) override;
	void onHackerModeEnable() override;
	void pause() override;
	void initializePositions() override;
	void initializeListeners() override;

	cocos2d::Vec2 getButtonOffset() override;
	void registerHackables() override;
	HackablePreview* createDefaultPreview() override;
	
	cocos2d::Vec2 getReparentPosition() override;

private:
	typedef MountBase super;
	
	enum class CartColor
	{
		Brown,
		Blue
	};

	void updateCanMove();
	void parseColor();

	CartColor cartColor = CartColor::Brown;
	CollisionObject* bottomCollision = nullptr;
	cocos2d::Sprite* body = nullptr;
	cocos2d::Sprite* wheelFront = nullptr;
	cocos2d::Sprite* wheelBack = nullptr;
	WorldSound* cartSfx = nullptr;

	static const std::string PropertyColor;
};
