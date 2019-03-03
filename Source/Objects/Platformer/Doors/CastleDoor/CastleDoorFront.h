#pragma once

#include "Engine/Maps/SerializableObject.h"

namespace cocos2d
{
	class Sprite;
}

class CastleDoorFront : public SerializableObject
{
public:
	static CastleDoorFront* create(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyCastleDoorFront;

protected:
	CastleDoorFront(cocos2d::ValueMap& initProperties);
	virtual ~CastleDoorFront();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef SerializableObject super;

	bool isFlipped;
	cocos2d::Sprite* castleDoorFront;
};
