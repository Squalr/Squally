#pragma once
#include <set>

#include "Engine/Hackables/HackableObject.h"

class CollisionObject;
class HackableData;
class InteractMenu;
class PlatformerEntity;
class Squally;

class PortalSpawn : public HackableObject
{
public:
	static PortalSpawn* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;
	static const std::string PropertyZoom;
	static const std::string PropertyPortalSpawnTransition;
	static const std::string PropertyMapBanner;

protected:
	PortalSpawn(cocos2d::ValueMap& properties);
	virtual ~PortalSpawn();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	virtual void onPlayerSpawn(PlatformerEntity* entity);

private:
	typedef HackableObject super;

	void doRelayer(PlatformerEntity* entity);
	void applyZoomOverride();
	void tryShowBanner();

	std::string transition;
	std::string bannerName;
	bool flipX;
	float zoomOverride;
};
