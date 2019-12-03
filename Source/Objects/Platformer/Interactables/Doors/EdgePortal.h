#pragma once

#include "Objects/Platformer/Interactables/Doors/Portal.h"

namespace cocos2d
{
	class Sprite;
};

class CollisionObject;

class EdgePortal : public Portal
{
public:
	static EdgePortal* create(cocos2d::ValueMap& properties);

	static const std::string MapKeyEdgePortal;

protected:
	EdgePortal(cocos2d::ValueMap& properties);
	~EdgePortal();
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef Portal super;

	std::vector<cocos2d::Sprite*> edgeArrows;
	CollisionObject* arrowHintCollision;

	static const int ArrowCount;
};
