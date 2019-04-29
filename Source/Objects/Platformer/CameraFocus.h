#pragma once

#include "Engine/Maps/SerializableObject.h"

class CameraFocus : public SerializableObject
{
public:
	static CameraFocus* create(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyCameraFocus;
	static const std::string MapKeyScrollBoundsX;
	static const std::string MapKeyScrollBoundsY;
	static const std::string MapKeyScrollSpeedX;
	static const std::string MapKeyScrollSpeedY;
	static const std::string MapKeyScrollType;

private:
	typedef SerializableObject super;
	CameraFocus(cocos2d::ValueMap& initProperties);
	~CameraFocus();

	cocos2d::Vec2 scrollBounds;
	cocos2d::Vec2 scrollSpeed;
	std::string scrollType;

	void onEnter() override;
};
