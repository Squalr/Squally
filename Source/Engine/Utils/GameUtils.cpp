#include "GameUtils.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCCamera.h"
#include "cocos/2d/CCParticleSystem.h"
#include "cocos/physics/CCPhysicsWorld.h"
#include "cocos/platform/CCFileUtils.h"

using namespace cocos2d;

// A better pause function that pauses recursively
void GameUtils::pause(Node *node)
{
	if (node == nullptr)
	{
		return;
	}

	// If the node is a scene node, pause physics
	if (dynamic_cast<const Scene*>(node) != nullptr)
	{
		const Scene* scene = dynamic_cast<const Scene*>(node);

		if (scene->getPhysicsWorld() != nullptr)
		{
			scene->getPhysicsWorld()->setSpeed(0.0f);
		}
	}

	node->pauseSchedulerAndActions();

	for (const auto &child : node->getChildren())
	{
		GameUtils::pause(child);
	}
}

void GameUtils::resume(Node *node)
{
	// If the node is a scene node, resume physics
	if (dynamic_cast<const Scene*>(node) != nullptr)
	{
		Scene* scene = (Scene*)node;

		if (scene->getPhysicsWorld() != nullptr)
		{
			scene->getPhysicsWorld()->setSpeed(1.0f);
		}
	}

	node->resumeSchedulerAndActions();

	for (const auto &child : node->getChildren())
	{
		GameUtils::resume(child);
	}
}

void GameUtils::resumeAll()
{
	GameUtils::resume(Director::getInstance()->getRunningScene());
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
	GameUtils::pause(Director::getInstance()->getRunningScene());
	GameUtils::resume(node);
}

void GameUtils::flattenNode(Node* parent)
{
	if (parent->getChildren().size() <= 0)
	{
		return;
	}

	Vector<Node*> children = parent->getChildren();

	for (auto it = children.begin(); it != children.end(); it++)
	{
		// Depth first recursion
		GameUtils::flattenNode(*it);
	}

	children = parent->getChildren();

	for (auto it = children.begin(); it != children.end(); it++)
	{
		Vector<Node*> childChildren = (*it)->getChildren();

		// Make the child's children siblings
		for (auto childIt = childChildren.begin(); childIt != childChildren.end(); childIt++)
		{
			GameUtils::changeParent(*childIt, parent, true);
		}
	}
}

Node* GameUtils::changeParent(Node* node, Node* newParent, bool retainPosition, int index)
{
	if (node == nullptr)
	{
		return node;
	}

	Vec2 newPosition = Vec2::ZERO;
	Node* previousParent = node->getParent();

	// Remove child from current parent
	if (previousParent != nullptr)
	{
		if (retainPosition && newParent != nullptr)
		{
			Vec2 screenPosition = previousParent->convertToWorldSpace(node->getPosition());
			newPosition = newParent->convertToNodeSpace(screenPosition);
		}

		node->retain();
		node->removeFromParent();
	}

	// Add or insert the child
	if (newParent != nullptr && index != -1)
	{
		newParent->addChildInsert(node, index, true);
	}
	else if (newParent != nullptr)
	{
		newParent->addChildAsReentry(node);
	}

	node->setPosition(newPosition);

	// Returns the same node that was given. Just a convenience thing for chaining methods.
	return node;
}

void GameUtils::accelerateParticles(ParticleSystem* particleSystem, float duration)
{
	const float step = 0.0166660007;

	particleSystem->start();

	for (float currentDuration = 0.0f; currentDuration < duration; currentDuration += step)
	{
		particleSystem->update(step);
	}
}

void GameUtils::fadeInObject(Node* node, float delay, float duration, GLubyte opacity)
{
	Sequence* sequence = Sequence::create(DelayTime::create(delay), FadeTo::create(duration, opacity), nullptr);

	node->setCascadeOpacityEnabled(true);
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

	if (node->getParent() != nullptr)
	{
		resultCoords = node->getParent()->convertToWorldSpace(resultCoords);
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

	if (node->getParent() != nullptr)
	{
		resultCoords = node->getParent()->convertToWorldSpace3(resultCoords);
	}

	return resultCoords;
}

Rect GameUtils::getScreenBounds(Node* node)
{
	if (Camera::getDefaultCamera() == nullptr || Director::getInstance() == nullptr)
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

bool GameUtils::intersects(Node* node, Vec2 mousePos)
{
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

bool GameUtils::keyExists(const ValueMap& valueMap, std::string key)
{
	auto pointsIterator = valueMap.find(key);

	if (pointsIterator != valueMap.end())
	{
		return true;
	}

	return false;
}

const cocos2d::Value& GameUtils::getKeyOrDefault(const ValueMap& valueMap, std::string key, const Value& defaultValue)
{
	if (GameUtils::keyExists(valueMap, key))
	{
		return valueMap.at(key);
	}

	return defaultValue;
}
