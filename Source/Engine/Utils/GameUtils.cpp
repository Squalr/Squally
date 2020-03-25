#include "GameUtils.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCCamera.h"
#include "cocos/2d/CCClippingNode.h"
#include "cocos/2d/CCParticleSystem.h"
#include "cocos/2d/CCScene.h"
#include "cocos/platform/CCFileUtils.h"

#include "Engine/UI/UIBoundObject.h"

using namespace cocos2d;

// A better pause function that pauses recursively
void GameUtils::pause(Node *node)
{
	if (node == nullptr)
	{
		return;
	}

	node->pause();

	for (const auto &child : node->getChildren())
	{
		GameUtils::pause(child);
	}
}

void GameUtils::resume(Node *node)
{
	node->resume();

	for (const auto &child : node->getChildren())
	{
		GameUtils::resume(child);
	}
}

void GameUtils::resumeAll()
{
	GameUtils::resume(Director::getInstance()->getRunningScene());
}

bool GameUtils::isInRunningScene(cocos2d::Node* node)
{
	return node == Director::getInstance()->getRunningScene()
		|| GameUtils::getFirstParentOfType<cocos2d::Scene>(node) == Director::getInstance()->getRunningScene();
}

Node* GameUtils::getFocusedNode()
{
	Node* root = Director::getInstance()->getRunningScene();
	std::function<Node*(Node*)> findUnpausedNodeRecursive;

	findUnpausedNodeRecursive = [=](Node* target)
	{
		Node* result = nullptr;

		if (!target->isPaused())
		{
			return target;
		}

		// Check immediate children first (BFS)
		for (const auto &child : target->getChildren())
		{
			if (!child->isPaused())
			{
				return child;
			}
		}

		// Recurse if nothing found
		for (const auto &child : target->getChildren())
		{
			result = findUnpausedNodeRecursive(child);

			if (result != nullptr)
			{
				return result;
			}
		}

		return result;
	};

	return findUnpausedNodeRecursive(root);
}

bool GameUtils::isFocused(Node *node)
{
	if (node->getParent() != nullptr && node->getParent()->isPaused() && !node->isPaused())
	{
		return true;
	}
	else if (node->getParent() == nullptr && !node->isPaused())
	{
		return true;
	}

	return false;
}

void GameUtils::focus(Node *node)
{
	if (node == nullptr)
	{
		return;
	}

	GameUtils::pause(Director::getInstance()->getRunningScene());
	GameUtils::resume(node);
}

void GameUtils::flattenNode(Node* parent)
{
	if (parent == nullptr || parent->getChildren().size() <= 0)
	{
		return;
	}

	Vector<Node*> children = parent->getChildren();

	for (auto child : children)
	{
		// Depth first recursion
		GameUtils::flattenNode(child);
	}

	children = parent->getChildren();

	for (auto child : children)
	{
		// Make the child's children siblings
		for (auto childChild : (child)->getChildren())
		{
			GameUtils::changeParent(childChild, parent, true);
		}
	}
}

Node* GameUtils::changeParent(Node* node, Node* newParent, bool retainPosition, bool addAsReentry, int index)
{
	if (node == nullptr)
	{
		return node;
	}
	
	Vec3 worldCoords = GameUtils::getWorldCoords3D(node);
	unsigned int refIncrement = 0;

	// Remove child from current parent
	if (node->getParent() != nullptr)
	{
		node->retain();
		node->getParent()->removeChildNoExit(node);
		node->softRelease();
	}

	// Add or insert the child
	if (newParent != nullptr && index != -1)
	{
		newParent->addChildInsert(node, index, true);
	}
	else if (newParent != nullptr)
	{
		if (addAsReentry)
		{
			newParent->addChildAsReentry(node);
		}
		else
		{
			newParent->addChild(node);
		}
	}

	if (retainPosition && newParent != nullptr)
	{
		node->setPosition3D(Vec3::ZERO);

		Vec3 newCoords = GameUtils::getWorldCoords3D(node);
		Vec3 delta = worldCoords - newCoords;

		node->setPosition3D(delta);

		if (GameUtils::getWorldCoords3D(node).distance(worldCoords) > 1.0f)
		{
			int pissant = 420;
		}
	}

	while (node->getReferenceCount() > 1 && refIncrement > 0)
	{
		node->release();
	}
	
	// Returns the same node that was given. Just a convenience thing for chaining methods.
	return node;
}

void GameUtils::fadeInObject(Node* node, float delay, float duration, GLubyte opacity)
{
	if (node == nullptr)
	{
		return;
	}

	Sequence* sequence = Sequence::create(DelayTime::create(delay), FadeTo::create(duration, opacity), nullptr);
	
	node->setOpacity(1); // Using 1 instead of 0 to avoid any GameUtils::isVisible check failures, while still being inperceptible
	node->runAction(sequence);
}

float GameUtils::getDepth(cocos2d::Node* node)
{
	float depth = 0.0f;

	while (node != nullptr)
	{
		depth += node->getPositionZ();

		node = node->getParent();
	}

	return depth;
}

float GameUtils::getRotation(cocos2d::Node* node)
{
	float rotation = 0.0f;

	while (node != nullptr)
	{
		rotation += node->getRotation();

		node = node->getParent();
	}

	return rotation;
}

float GameUtils::getScale(cocos2d::Node* node)
{
	float scale = 1.0f;

	while (node != nullptr)
	{
		scale *= node->getScale();

		node = node->getParent();
	}

	return scale;
}

Vec2 GameUtils::getWorldCoords(Node* node)
{
	if (node == nullptr)
	{
		return Vec2::ZERO;
	}

	Rect resultRect = node->getBoundingBox();
	Vec2 resultCoords = Vec2(resultRect.getMinX() - resultRect.size.width / 2.0f, resultRect.getMinY() - resultRect.size.height / 2.0f);
	Node* parent = node->getParent();
	UIBoundObject* uiBoundObjectParent = GameUtils::getFirstParentOfType<UIBoundObject>(parent);

	// Special conditions for a ui-bound object
	if (uiBoundObjectParent != nullptr)
	{
		Vec2 relativeCoords = uiBoundObjectParent->convertToWorldSpace(resultCoords);
		Vec3 realCoords = UIBoundObject::getRealCoords(uiBoundObjectParent);
		Vec2 fixedCoords = Vec2(realCoords.x, realCoords.y) + Vec2(relativeCoords.x, -resultRect.size.height / 2.0f);

		return fixedCoords;
	}

	if (parent != nullptr)
	{
		resultCoords = parent->convertToWorldSpace(resultCoords);
	}

	return resultCoords;
}

Vec3 GameUtils::getWorldCoords3D(Node* node)
{
	if (node == nullptr)
	{
		return Vec3::ZERO;
	}

	Rect resultRect = node->getBoundingBox();
	Vec3 resultCoords = Vec3(resultRect.getMinX() - resultRect.size.width / 2.0f, resultRect.getMinY() - resultRect.size.height / 2.0f, node->getPositionZ());
	Node* parent = node->getParent();
	UIBoundObject* uiBoundObjectParent = GameUtils::getFirstParentOfType<UIBoundObject>(parent);

	// Special conditions for a ui-bound object
	if (uiBoundObjectParent != nullptr)
	{
		uiBoundObjectParent->pushRealPosition();
	}

	if (parent != nullptr)
	{
		resultCoords = parent->convertToWorldSpace3(resultCoords);
	}

	// Special conditions for a ui-bound object
	if (uiBoundObjectParent != nullptr)
	{
		uiBoundObjectParent->popRealPosition();
	}

	return resultCoords;
}

void GameUtils::setWorldCoords3D(Node* node, cocos2d::Vec3 worldCoords)
{
	if (node == nullptr)
	{
		return;
	}

	Vec3 currentCoords = GameUtils::getWorldCoords3D(node);
	Vec3 delta = worldCoords - currentCoords;

	node->setPosition3D(node->getPosition3D() + delta);
}

Rect GameUtils::getScreenBounds(Node* node)
{
	if (node == nullptr || Camera::getDefaultCamera() == nullptr || Director::getInstance() == nullptr)
	{
		return Rect::ZERO;
	}

	Rect worldRect = node->getBoundingBoxNoTransform();
	Vec3 worldCoordsA = GameUtils::getWorldCoords3D(node);
	Vec3 worldCoordsB = worldCoordsA + Vec3(worldRect.size.width, worldRect.size.height, 0.0f) * GameUtils::getScale(node);

	Vec2 resultCoordsA = Camera::getDefaultCamera()->projectGL(worldCoordsA);
	Vec2 resultCoordsB = Camera::getDefaultCamera()->projectGL(worldCoordsB);
	Rect resultRect = Rect(resultCoordsA, Size(resultCoordsB - resultCoordsA));

	return resultRect;
}

bool GameUtils::isVisible(Node* node)
{
	while (node != nullptr)
	{
		if (!node->isVisible() || node->getOpacity() <= 0)
		{
			return false;
		}

		node = node->getParent();
	}

	return true;
}

bool GameUtils::isEclipsed(Node* node, cocos2d::Vec2 mousePos)
{
	ClippingNode* parentClip = GameUtils::getFirstParentOfType<ClippingNode>(node);

	if (parentClip != nullptr)
	{
		Rect clippingBounds = GameUtils::getScreenBounds(parentClip);
		Rect mouseRect = Rect(mousePos.x, mousePos.y, 1.0f, 1.0f);

		// Correction has to be made for whatever reason, don't question it
		clippingBounds.origin += Vec2(clippingBounds.size / 2.0f);

		// If not clicking within the clip-safe region, the click is eclipsed
		if (!clippingBounds.intersectsRect(mouseRect))
		{
			return true;
		}
	}

	return false;
}

bool GameUtils::intersects(Node* node, Vec2 mousePos)
{
	if (GameUtils::isEclipsed(node, mousePos))
	{
		return false;
	}

	Rect mouseRect = Rect(mousePos.x, mousePos.y, 1.0f, 1.0f);

	if (GameUtils::getScreenBounds(node).intersectsRect(mouseRect))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool GameUtils::intersectsIsometric(Node* node, Vec2 mousePos)
{
	if (GameUtils::isEclipsed(node, mousePos))
	{
		return false;
	}

	Rect mouseRect = Rect(mousePos.x, mousePos.y, 1.0f, 1.0f);
	Rect nodeBounds = GameUtils::getScreenBounds(node);

	float dx = std::abs(mousePos.x - nodeBounds.getMidX());
	float dy = std::abs(mousePos.y - nodeBounds.getMidY());

	if (nodeBounds.size.width > 0.0f && nodeBounds.size.height > 0.0f && (dx / nodeBounds.size.width + dy / nodeBounds.size.height <= 1.0f))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool GameUtils::keyExists(const ValueMap& valueMap, std::string key)
{
	auto pointsIterator = valueMap.find(key);

	if (pointsIterator != valueMap.end())
	{
		return true;
	}

	return false;
}

bool GameUtils::hasArg(const std::vector<std::string>& argList, std::string arg)
{
	return (std::find(argList.begin(), argList.end(), arg) != argList.end());
}

const cocos2d::Value& GameUtils::getKeyOrDefault(const ValueMap& valueMap, std::string key, const Value& defaultValue)
{
	if (GameUtils::keyExists(valueMap, key))
	{
		return valueMap.at(key);
	}

	return defaultValue;
}

void GameUtils::deleteKey(cocos2d::ValueMap& valueMap, std::string key)
{
	if (GameUtils::keyExists(valueMap, key))
	{
		valueMap.erase(key);
	}
}
