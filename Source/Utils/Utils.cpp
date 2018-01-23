#include "Utils.h"

// A better pause function that pauses recursively
void Utils::pause(Node *node)
{
	// If the node is a scene node, pause physics
	if (dynamic_cast<const Scene*>(node) != nullptr)
	{
		Director::getInstance()->getRunningScene()->getPhysicsWorld()->setSpeed(0.0f);
	}

	node->pauseSchedulerAndActions();

	for (const auto &child : node->getChildren())
	{
		Utils::pause(child);
	}
}

// A better resume function that resumes recursively
void Utils::resume(Node *node)
{
	// If the node is a scene node, resume physics
	if (dynamic_cast<const Scene*>(node) != nullptr)
	{
		Director::getInstance()->getRunningScene()->getPhysicsWorld()->setSpeed(1.0f);
	}

	node->resumeSchedulerAndActions();

	for (const auto &child : node->getChildren())
	{
		Utils::resume(child);
	}
}

void Utils::resumeAll()
{
	Utils::resume(Director::getInstance()->getRunningScene());
}

void Utils::focus(Node *node)
{
	Utils::pause(Director::getInstance()->getRunningScene());
	Utils::resume(node);
	node->addChild(Mouse::claimInstance());
}

void Utils::accelerateParticles(ParticleSystem* particleSystem, float duration)
{
	const float step = 0.0166660007;

	particleSystem->start();

	for (float currentDuration = 0.0f; currentDuration < duration; currentDuration += step)
	{
		particleSystem->update(step);
	}
}

void Utils::fadeInObject(Node* node, float delay, float duration)
{
	Sequence* sequence = Sequence::create(DelayTime::create(delay), FadeIn::create(duration), nullptr);

	node->setCascadeOpacityEnabled(true);
	node->setOpacity(0);
	node->runAction(sequence);
}

Rect Utils::getSceneBounds(Node* node)
{
	Rect resultRect = node->getBoundingBox();
	Vec2 resultCoords = Vec2(resultRect.getMinX() - resultRect.size.width / 2, resultRect.getMinY() - resultRect.size.height / 2);
	Vec2 resultSize = Vec2(resultRect.size.width, resultRect.size.height);

	if (node->getParent() != nullptr)
	{
		resultCoords = node->getParent()->convertToWorldSpace(resultCoords);
	}

	resultRect.setRect(resultCoords.x, resultCoords.y, resultSize.x, resultSize.y);

	return resultRect;
}

bool Utils::isVisible(Node* node)
{
	while (node != nullptr)
	{
		if (!node->isVisible())
		{
			return false;
		}

		node = node->getParent();
	};

	return true;
}

bool Utils::intersects(Node* node, Vec2 mousePos)
{
	Rect mouseRect = Rect(mousePos.x, mousePos.y, 1.0f, 1.0f);

	if (Utils::getSceneBounds(node).intersectsRect(mouseRect))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Utils::keyExists(ValueMap valueMap, std::string key)
{
	auto pointsIterator = valueMap.find(key);

	if (pointsIterator != valueMap.end())
	{
		return true;
	}

	return false;
}
