#pragma once

#include "Engine/Maps/GameObject.h"

class CameraTarget;
class CollisionObject;

class CameraControl : public GameObject
{
public:
	static CameraControl* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	CameraControl(cocos2d::ValueMap& properties);
	virtual ~CameraControl();

	void initializeListeners() override;

private:
	typedef GameObject super;

	void beginTrack();
	void endTrack();

	CollisionObject* controlCollision;
	CameraTarget* cameraTarget;
	std::string targetTag;

	static const std::string PropertyTarget;
};
