#pragma once

#include "Engine/Maps/GameObject.h"

class CollisionObject;

class MiniMapRelocator : public GameObject
{
public:
	static MiniMapRelocator* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	MiniMapRelocator(cocos2d::ValueMap& properties);
	virtual ~MiniMapRelocator();

	void initializeListeners() override;

private:
	typedef GameObject super;

	void positionMiniMap();
	void endPositionMiniMap();

	std::string position;
	CollisionObject* triggerCollision;

	static const std::string PropertyPosition;
};
