#pragma once
#include <set>

#include "Objects/Platformer/Interactables/Doors/Portal.h"

namespace cocos2d
{
	class DrawNode;
}

class SmartClippingNode;
class WorldSound;

class MagePortal : public Portal
{
public:
	static MagePortal* create(cocos2d::ValueMap& properties);

	virtual void closePortal(bool instant);
	virtual void openPortal(bool instant);

	static const std::string MapKey;

protected:
	MagePortal(cocos2d::ValueMap& properties);
	virtual ~MagePortal();
	
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void drawEdge(cocos2d::Color4F edgeColor, cocos2d::DrawNode* drawNode, float radius, int thickness);

	cocos2d::Node* portalEffectNode;

private:
	typedef Portal super;

	SmartClippingNode* portalBase;
	cocos2d::Node* portalContentNode;
	cocos2d::DrawNode* background;
	cocos2d::DrawNode* edge;
	WorldSound* portalOpenSound;

	SmartParticles* portalParticles;
	SmartParticles* edgeParticles;
	
	static const float PortalRadius;
	static const cocos2d::Color4B BaseColor;
};
