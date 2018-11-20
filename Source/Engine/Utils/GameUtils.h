#pragma once
#include "cocos/math/CCGeometry.h"

#include "Engine/UI/Mouse.h"
#include "StrUtils.h"

namespace cocos2d
{
	class Node;
}

class GameUtils
{
public:
	static std::vector<std::string> getAllAnimationFiles(std::string firstFrameResource);
	static void pause(cocos2d::Node *node);
	static void resume(cocos2d::Node *node);
	static void resumeAll();
	static bool isFocused(cocos2d::Node *node);
	static void focus(cocos2d::Node *node);
	static void flattenNode(cocos2d::Node* node);
	static cocos2d::Node* changeParent(cocos2d::Node* node, cocos2d::Node* newParent, bool retainPosition, int index = -1);
	static void accelerateParticles(ParticleSystem* particleSystem, float duration);
	static void fadeInObject(cocos2d::Node* node, float delay, float duration, GLubyte opacity = 255);
	static cocos2d::Rect getSceneBounds(cocos2d::Node* node);
	static cocos2d::Rect getSceneBoundsV2(cocos2d::Node* node);
	static bool isVisible(cocos2d::Node* node);
	static bool intersects(cocos2d::Node* node, Vec2 mousePos);
	static bool intersectsV2(cocos2d::Node* node, Vec2 mousePos);
	static bool keyExists(ValueMap* valueMap, std::string key);
};

