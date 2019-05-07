#pragma once

#include "Engine/Maps/SerializableObject.h"

class Hud;

class CameraScrollTracker : public SerializableObject
{
public:
	static CameraScrollTracker* create(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyCameraScrollTracker;
	static const std::string MapKeyZoom;
	static const std::string MapKeyScrollSpeed;

private:
	typedef SerializableObject super;
	CameraScrollTracker(cocos2d::ValueMap& initProperties);
	~CameraScrollTracker();

	void onEnter() override;
	void onEnterTransitionDidFinish() override;
	void initializeListeners() override;
	void scrollBy(float percentage);

	float zoom;
	float scrollDistance;
	Hud* hud;
	cocos2d::Node* trackTarget;
	cocos2d::Vec2 source;
	cocos2d::Vec2 dest;

	static const float ScrollSpeed;
};
