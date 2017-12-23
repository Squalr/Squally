#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class Utils
{
public:
	static std::string HexAddressOf(void* address);
	static bool Intersects(Node* node, Vec2 mousePos);
};

