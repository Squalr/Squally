#pragma once

#include "Engine/Camera/CameraTrackingData.h"
#include "Engine/Maps/GameObject.h"

namespace cocos2d
{
	class DrawNode;
}

class CameraTrackingData;

class CameraTarget : public GameObject
{
public:
	static CameraTarget* create(cocos2d::ValueMap& properties);

	CameraTrackingData getTrackingData();

	static const std::string MapKeyCameraTarget;

private:
	typedef GameObject super;
	CameraTarget(cocos2d::ValueMap& properties);
	virtual ~CameraTarget();

	void onEnter() override;
	void onDeveloperModeEnable() override;
	void onDeveloperModeDisable() override;

	cocos2d::DrawNode* debugDraw;
	float zoom;

	static const std::string MapPropertyZoom;
};
