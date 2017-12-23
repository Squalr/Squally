#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class Utils
{
public:
	static std::string HexAddressOf(void* address);
	static Rect GetSceneBounds(Node* node);
	static bool Intersects(Node* node, Vec2 mousePos);
	static bool KeyExists(ValueMap valueMap, std::string key);
};

