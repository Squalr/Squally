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

	cocos2d::Node* portalEffectNode = nullptr;

private:
	typedef Portal super;

	SmartClippingNode* portalBase = nullptr;
	cocos2d::Node* portalContentNode = nullptr;
	cocos2d::DrawNode* background = nullptr;
	cocos2d::DrawNode* edge = nullptr;
	WorldSound* portalOpenSound = nullptr;

	SmartParticles* portalParticles = nullptr;
	SmartParticles* edgeParticles = nullptr;
	
	static const float PortalRadius;
	static const cocos2d::Color4B BaseColor;
};
