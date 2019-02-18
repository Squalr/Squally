#pragma once
#include <map>
#include <string>
#include "cocos/2d/CCNode.h"
#include "cocos/math/CCGeometry.h"

namespace cocos2d
{
	class ParticleSystem;
	class Value;
	typedef std::map<std::string, Value> ValueMap;
}

class GameUtils
{
public:
	static void pause(cocos2d::Node *node);
	static void resume(cocos2d::Node *node);
	static void resumeAll();
	static cocos2d::Node* getFocusedNode();
	static bool isFocused(cocos2d::Node *node);
	static void focus(cocos2d::Node *node);
	static void flattenNode(cocos2d::Node* node);
	static cocos2d::Node* changeParent(cocos2d::Node* node, cocos2d::Node* newParent, bool retainPosition, int index = -1);
	static void accelerateParticles(cocos2d::ParticleSystem* particleSystem, float duration);
	static void fadeInObject(cocos2d::Node* node, float delay, float duration, uint8_t opacity = 255);
	static float getDepth(cocos2d::Node* node);
	static float getScale(cocos2d::Node* node);
	static cocos2d::Vec2 getWorldCoords(cocos2d::Node* node);
	static cocos2d::Vec3 getWorldCoords3D(cocos2d::Node* node);
	static cocos2d::Rect getScreenBounds(cocos2d::Node* node);
	static bool isVisible(cocos2d::Node* node);
	static bool intersects(cocos2d::Node* node, cocos2d::Vec2 mousePos);
	static bool keyExists(cocos2d::ValueMap& valueMap, std::string key);
	static cocos2d::Value& getKeyOrDefault(cocos2d::ValueMap& valueMap, std::string key, cocos2d::Value defaultValue);

	template <class T>
	static T* getFirstParentOfType(cocos2d::Node *node)
	{
		while (node != nullptr)
		{
			if (dynamic_cast<T*>(node) != nullptr)
			{
				return dynamic_cast<T*>(node);
			}

			node = node->getParent();
		}

		return nullptr;
	}
};
