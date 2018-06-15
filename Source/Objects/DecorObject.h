#pragma once
#include "cocos2d.h"

#include "Engine/Maps/SerializableObject.h"
#include "Scenes/Level/LevelCamera.h"

using namespace cocos2d;

class DecorObject : public SerializableObject
{
public:
	static DecorObject* create();

private:
	DecorObject();
	~DecorObject();
};
