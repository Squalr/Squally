#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class Utils
{
public:
	static std::string hexAddressOf(void* address);
	static void accelerateParticles(ParticleSystem* particleSystem, float duration);
	static void fadeInObject(Node* node, float delay, float duration);
	static Rect getSceneBounds(Node* node);
	static bool intersects(Node* node, Vec2 mousePos);
	static bool keyExists(ValueMap valueMap, std::string key);
};

