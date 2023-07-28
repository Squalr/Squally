#pragma once
#include <set>

#include "Objects/Platformer/Interactables/Doors/Portal.h"

class ClickableHackNode;
class LocalizedString;

namespace cocos2d
{
	class Sprite;
};

class HackableWarp : public Portal
{
public:
	static HackableWarp* create(cocos2d::ValueMap& properties);
	
	std::string getStrKey();

	static const std::string MapKey;

protected:
	HackableWarp(cocos2d::ValueMap& properties);
	virtual ~HackableWarp();
	
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void loadMap() override;

private:
	typedef Portal super;

	void doRelayer();

	ClickableHackNode* warpHitbox = nullptr;
};
