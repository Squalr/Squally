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
	static bool isInRunningScene(cocos2d::Node *node);
	static cocos2d::Node* getFocusedNode();
	static bool isFocused(cocos2d::Node *node);
	static void focus(cocos2d::Node *node);
	static void flattenNode(cocos2d::Node* node);
	static cocos2d::Node* changeParent(cocos2d::Node* node, cocos2d::Node* newParent, bool retainPosition, bool addAsReentry = true, int index = -1);
	static void fadeInObject(cocos2d::Node* node, float delay, float duration, uint8_t opacity = 255);
	static float getDepth(cocos2d::Node* node);
	static float getRotation(cocos2d::Node* node);
	static float getScale(cocos2d::Node* node);
	static cocos2d::Vec2 getMapCoords(cocos2d::Node* node, bool checkForUIBound = true);
	static cocos2d::Vec3 getMapCoords3D(cocos2d::Node* node, bool checkForUIBound = true);
	static cocos2d::Vec2 getWorldCoords(cocos2d::Node* node, bool checkForUIBound = true);
	static cocos2d::Vec3 getWorldCoords3D(cocos2d::Node* node, bool checkForUIBound = true);
	static void setWorldCoords(cocos2d::Node* node, cocos2d::Vec2 worldCoords);
	static void setWorldCoords3D(cocos2d::Node* node, cocos2d::Vec3 worldCoords);
	static cocos2d::Vec2 getScreenCoords(const cocos2d::Vec3& point);
	static cocos2d::Rect getScreenBounds(cocos2d::Node* node, const cocos2d::Size& padding = cocos2d::Size::ZERO);
	static cocos2d::Rect getScreenBounds(const cocos2d::Vec3& position, const cocos2d::Size& size);
	static bool isVisible(cocos2d::Node* node);
	static bool isEclipsed(cocos2d::Node* node, cocos2d::Vec2 mousePos);
	static bool intersects(cocos2d::Node* node, cocos2d::Vec2 mousePos);
	static bool intersectsIsometric(cocos2d::Node* node, cocos2d::Vec2 mousePos);
	static bool keyExists(const cocos2d::ValueMap& valueMap, std::string key);
	static void deleteKey(cocos2d::ValueMap& valueMap, std::string key);
	static bool hasArg(const std::vector<std::string>& argList, std::string arg);
	static const cocos2d::Value& getKeyOrDefault(const cocos2d::ValueMap& valueMap, std::string key, const cocos2d::Value& defaultValue);

	template <class T>
	static bool isVisibleUntil(cocos2d::Node* node)
	{
		while (node != nullptr)
		{
			if (dynamic_cast<T*>(node) != nullptr)
			{
				return true;
			}

			if (!node->isVisible() || node->getOpacity() <= 0)
			{
				return false;
			}

			node = node->getParent();
		}

		return true;
	}

	template <class T>
	static float getDepthUntil(cocos2d::Node* node)
	{
		float depth = 0.0f;

		while (node != nullptr)
		{
			depth += node->getPositionZ();

			if (dynamic_cast<T*>(node) != nullptr)
			{
				break;
			}

			node = node->getParent();
		}

		return depth;
	}

	template <class T>
	static T* getFirstParentOfType(cocos2d::Node *node, bool includeTarget = false)
	{
		if (node != nullptr && !includeTarget)
		{
			node = node->getParent();
		}
		
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
	
	// This function is O(n) and should be used sparringly
	template <class T>
	static void getChildrenOfType(cocos2d::Node *node, std::function<void(T*)> onFound, bool recurseOnFound = false)
	{
		if (node == nullptr)
		{
			return;
		}

		for (auto next : node->getChildren())
		{
			if (dynamic_cast<T*>(next) != nullptr)
			{
				onFound(dynamic_cast<T*>(next));

				if (recurseOnFound)
				{
					getChildrenOfType(next, onFound, recurseOnFound);
				}
			}
			else
			{
				getChildrenOfType(next, onFound, recurseOnFound);
			}
		}
	}
};
