#pragma once

#include "Engine/Maps/GameObject.h"

namespace cocos2d
{
	class Sprite;
}

class CastleDoorFront : public GameObject
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
	typedef GameObject super;

	bool isFlipped;
	cocos2d::Sprite* castleDoorFront;
};
