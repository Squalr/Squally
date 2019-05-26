#pragma once
#include <set>

#include "Engine/Maps/SerializableObject.h"

namespace cocos2d
{
	class ParticleSystem;
}

class CollisionObject;
class HackableData;

class EdgePortal : public SerializableObject
{
public:
	static EdgePortal* create(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyEdgePortal;

protected:
	EdgePortal(cocos2d::ValueMap& initProperties);
	~EdgePortal();
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef SerializableObject super;

	CollisionObject* edgePortalCollision;
	CollisionObject* edgePortalHintCollision;

	bool wasTripped;
	bool isLocked;
	std::string mapFile;
	std::string mapArgs;

	static const std::string MapKeyEdgePortalArgs;
	static const std::string MapKeyEdgePortalDirection;
	static const std::string MapKeyEdgePortalMap;
};
