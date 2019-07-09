#pragma once

#include "Engine/Maps/GameObject.h"

class CameraFocus : public GameObject
{
public:
	static CameraFocus* create(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyCameraFocus;
	static const std::string MapKeyZoom;
	static const std::string MapKeyScrollBoundsX;
	static const std::string MapKeyScrollBoundsY;
	static const std::string MapKeyScrollSpeedX;
	static const std::string MapKeyScrollSpeedY;
	static const std::string MapKeyScrollType;

private:
	typedef GameObject super;
	CameraFocus(cocos2d::ValueMap& initProperties);
	~CameraFocus();

	void onEnter() override;
	void onEnterTransitionDidFinish() override;

	float zoom;
	cocos2d::Vec2 scrollBounds;
	cocos2d::Vec2 scrollSpeed;
	std::string scrollType;
};
