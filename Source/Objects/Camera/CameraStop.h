#pragma once

#include "Engine/Maps/GameObject.h"

class CameraStop : public GameObject
{
public:
	static CameraStop* create(cocos2d::ValueMap& properties);

	static const std::string MapKeyCameraStop;

private:
	typedef GameObject super;
	CameraStop(cocos2d::ValueMap& properties);
	~CameraStop();

	void update(float dt) override;
};
