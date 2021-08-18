#pragma once

#include "Engine/Maps/GameObject.h"

class Squally;
class TrackingEye;

class TrackingEyeController : public GameObject
{
public:
	static TrackingEyeController* create(cocos2d::ValueMap& properties);

	void pair(TrackingEyeController* pairedEye);

	static const std::string MapKey;

protected:
	TrackingEyeController(cocos2d::ValueMap& properties);
	virtual ~TrackingEyeController();

	void onEnter() override;
	void update(float dt) override;

private:
	typedef GameObject super;

	void updateEyeTracking(float dt);

	struct EyeData
	{
		TrackingEye* eye = nullptr;
		cocos2d::Vec2 coords;

		EyeData(TrackingEye* eye, cocos2d::Vec2 coords) : eye(eye), coords(coords) { }
	};
	
	Squally* squally = nullptr;
	std::vector<EyeData> eyes;
	std::string eyeGroup;

	static const std::string PropertyEyeGroup;
};
