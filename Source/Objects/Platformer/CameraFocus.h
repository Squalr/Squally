#pragma once

#include "Engine/Maps/SerializableObject.h"

class CameraFocus : public SerializableObject
{
public:
	static CameraFocus* create(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyCameraFocus;

private:
	CameraFocus(cocos2d::ValueMap* initProperties);
	~CameraFocus();

	void onEnter() override;
};
