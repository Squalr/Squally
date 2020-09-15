#pragma once

#include "Objects/Platformer/Interactables/Doors/Portal.h"

namespace cocos2d
{
	class Sprite;
}

class TrackingEye;

class ScreamingDoor : public Portal
{
public:
	static ScreamingDoor* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	ScreamingDoor(cocos2d::ValueMap& properties);
	virtual ~ScreamingDoor();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef Portal super;

	cocos2d::Sprite* screamingDoor;

	TrackingEye* leftEye;
	TrackingEye* rightEye;
};
