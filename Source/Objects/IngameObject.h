#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Level/LevelCamera.h"
#include "Objects/Hackables/HackableObject.h"

using namespace cocos2d;

class IngameObject : public Node
{
public:
	IngameObject();
	~IngameObject();

	virtual HackableObject* getHackableObject();
};
