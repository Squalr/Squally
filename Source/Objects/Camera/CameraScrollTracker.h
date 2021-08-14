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

protected:
	CameraScrollTracker(cocos2d::ValueMap& properties);
	virtual ~CameraScrollTracker();

	void onEnter() override;
	void onEnterTransitionDidFinish() override;
	void initializeListeners() override;
	void scrollBy(float percentage);

private:
	typedef GameObject super;

	float zoom = 0.0f;
	float scrollDistance = 0.0f;
	Hud* hud = nullptr;
	cocos2d::Node* trackTarget = nullptr;
	cocos2d::Vec2 source;
	cocos2d::Vec2 dest;

	static const float ScrollSpeed;
};
