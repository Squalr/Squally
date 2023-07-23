#pragma once
#include <set>

#include "Objects/Platformer/Interactables/Doors/Portal.h"

class Warp : public Portal
{
public:
	static Warp* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;
	static const std::string PropertyWarpFrom;
	static const std::string PropertyWarpTo;
	static const std::string PropertyNoWarpCamera;
	static const std::string PropertyRelayer;
	static const std::string PropertySaveKey;

protected:
	Warp(cocos2d::ValueMap& properties);
	virtual ~Warp();
	
	void onEnter() override;
	void initializeListeners() override;
	void update(float dt) override;
	void loadMap() override;

private:
	typedef Portal super;

	void doRelayer();

	std::string from;
	std::string to;
	std::string saveKey;
	bool warpCamera = false;
	bool relayer = false;
	float cooldown = 0.0f;

	static const std::string EventWarpToPrefix;
	static const float WarpCooldown;
};
