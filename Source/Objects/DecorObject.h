#pragma once
#include "cocos2d.h"

#include "Objects/Hackables/HackableObject.h"
#include "Scenes/Level/LevelCamera.h"

using namespace cocos2d;

class DecorObject : public HackableObject
{
public:
	static DecorObject* create(ValueMap* initProperties);

private:
	DecorObject(ValueMap* initProperties);
	~DecorObject();
};
