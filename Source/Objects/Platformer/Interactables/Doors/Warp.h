#pragma once
#include <set>

#include "Objects/Platformer/Interactables/Doors/Portal.h"

class Warp : public Portal
{
public:
	static Warp* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;
	static const std::string MapKeyWarpFrom;
	static const std::string MapKeyWarpTo;

protected:
	Warp(cocos2d::ValueMap& properties);
	virtual ~Warp();
	
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void loadMap() override;

private:
	typedef Portal super;

	std::string from;
	std::string to;

	static const std::string EventWarpToPrefix;
};
