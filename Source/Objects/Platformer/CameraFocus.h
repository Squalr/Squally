#pragma once
#include "cocos2d.h"

#include "Engine/Maps/SerializableObject.h"

using namespace cocos2d;

class CameraFocus : public SerializableObject
{
public:
	static CameraFocus* create(ValueMap* initProperties);

	static const std::string MapKeyCameraFocus;

private:
	CameraFocus(ValueMap* initProperties);
	~CameraFocus();

	void onEnter() override;

};
