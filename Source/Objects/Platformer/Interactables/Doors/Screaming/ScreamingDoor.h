#pragma once

#include "Objects/Platformer/Interactables/Doors/Portal.h"

namespace cocos2d
{
	class Sprite;
}

class TrackingEye;
class TrackingEyeController;

class ScreamingDoor : public Portal
{
public:
	static ScreamingDoor* create(cocos2d::ValueMap& properties);
	
	void lock(bool animate = true) override;
	void unlock(bool animate = true) override;

	static const std::string MapKey;

protected:
	ScreamingDoor(cocos2d::ValueMap& properties);
	virtual ~ScreamingDoor();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef Portal super;

	cocos2d::Sprite* screamingDoor = nullptr;
	cocos2d::Sprite* screamingDoorLocked = nullptr;
	TrackingEyeController* eyeController = nullptr;
	TrackingEye* leftEye = nullptr;
	TrackingEye* rightEye = nullptr;
};
