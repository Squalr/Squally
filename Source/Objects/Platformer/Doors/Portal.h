#pragma once
#include <set>

#include "Engine/Hackables/HackableObject.h"

class CollisionObject;
class HackableData;
class InteractMenu;

class Portal : public HackableObject
{
public:
	static const std::string MapKeyPortalArgs;
	static const std::string MapKeyPortalMap;
	static const std::string MapKeyPortalTransition;

	void setLocked(bool isLocked);
	void setRequiresInteraction(bool requiresInteraction);

protected:
	Portal(cocos2d::ValueMap& initProperties, cocos2d::Size size, cocos2d::Vec2 offset = cocos2d::Vec2::ZERO);
	~Portal();
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef HackableObject super;

	void loadMap();

	CollisionObject* portalCollision;
	InteractMenu* interactMenu;

	bool canInteract;
	bool wasTripped;
	bool isLocked;
	bool requiresInteraction;
	std::string mapFile;
	std::vector<std::string> mapArgs;
};
