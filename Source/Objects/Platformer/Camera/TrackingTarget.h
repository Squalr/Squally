#pragma once

#include "Engine/Maps/GameObject.h"

namespace cocos2d
{
	class DrawNode;
}

class TrackingTarget : public GameObject
{
public:
	static TrackingTarget* create(cocos2d::ValueMap& properties);

	static const std::string MapKeyTrackingTarget;

private:
	typedef GameObject super;
	TrackingTarget(cocos2d::ValueMap& properties);
	virtual ~TrackingTarget();

	void onEnter() override;
	void onDeveloperModeEnable() override;
	void onDeveloperModeDisable() override;

	cocos2d::DrawNode* debugDraw;
	float zoom;

	static const std::string MapPropertyZoom;
};
