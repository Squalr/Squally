#pragma once

#include "Engine/Maps/GameObject.h"

class Hud;

class CameraScrollTracker : public GameObject
{
public:
	static CameraScrollTracker* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;
	static const std::string MapKeyZoom;
	static const std::string MapKeyScrollSpeed;

private:
	typedef GameObject super;
	CameraScrollTracker(cocos2d::ValueMap& properties);
	virtual ~CameraScrollTracker();

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
