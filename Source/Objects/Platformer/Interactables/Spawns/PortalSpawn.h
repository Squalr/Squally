#pragma once
#include <set>

#include "Engine/Hackables/HackableObject.h"

class CollisionObject;
class HackableData;
class InteractMenu;

class PortalSpawn : public HackableObject
{
public:
	static PortalSpawn* create(cocos2d::ValueMap& properties);

	static const std::string MapKeyPortalSpawn;

protected:
	PortalSpawn(cocos2d::ValueMap& properties);
	virtual ~PortalSpawn();
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	virtual void onPlayerSpawn();

private:
	typedef HackableObject super;

	void tryShowBanner();

	std::string transition;
	std::string bannerName;
	
	static const std::string MapKeyPortalSpawnTransition;
	static const std::string MapKeyMapBanner;
};
