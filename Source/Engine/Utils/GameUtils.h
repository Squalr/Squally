#pragma once
#include "cocos2d.h"

#include "Engine/UI/Mouse.h"

#include "StrUtils.h"

using namespace cocos2d;

class GameUtils
{
public:
	static std::vector<std::string> getAllAnimationFiles(std::string firstFrameResource);
	static void pause(Node *node);
	static void resume(Node *node);
	static void resumeAll();
	static bool isFocused(Node *node);
	static void focus(Node *node);
	static void flattenNode(Node* node);
	static Node* changeParent(Node* node, Node* newParent, bool retainPosition);
	static void accelerateParticles(ParticleSystem* particleSystem, float duration);
	static void fadeInObject(Node* node, float delay, float duration);
	static Rect getSceneBounds(Node* node);
	static Rect getSceneBoundsV2(Node* node);
	static bool isVisible(Node* node);
	static bool intersects(Node* node, Vec2 mousePos);
	static bool intersectsV2(Node* node, Vec2 mousePos);
	static bool keyExists(ValueMap* valueMap, std::string key);
};

