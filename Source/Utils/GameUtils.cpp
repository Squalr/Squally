#include "GameUtils.h"

const std::string GameUtils::gameNavigateNewEvent = "game_navigate_new_event";
const std::string GameUtils::gameNavigateBackEvent = "game_navigate_back_event";
const std::string GameUtils::gameNavigateNewLevelEvent = "game_navigate_new_level_event";

void GameUtils::navigateBack(int count)
{
	Director::getInstance()->getRunningScene()->getEventDispatcher()->dispatchCustomEvent(
		GameUtils::gameNavigateBackEvent,
		&NavigateBackEventArgs(count)
	);
}

void GameUtils::navigate(GameScreen gameScreen)
{
	Director::getInstance()->getRunningScene()->getEventDispatcher()->dispatchCustomEvent(
		GameUtils::gameNavigateNewEvent,
		&NavigateEventArgs(gameScreen)
	);
}

void GameUtils::loadLevel(std::string levelFile)
{
	Director::getInstance()->getRunningScene()->getEventDispatcher()->dispatchCustomEvent(
		GameUtils::gameNavigateNewLevelEvent,
		&NavigateNewLevelEvent(levelFile)
	);
}

// A better pause function that pauses recursively
void GameUtils::pause(Node *node)
{
	// If the node is a scene node, pause physics
	if (dynamic_cast<const Scene*>(node) != nullptr)
	{
		Director::getInstance()->getRunningScene()->getPhysicsWorld()->setSpeed(0.0f);
	}

	node->pauseSchedulerAndActions();

	for (const auto &child : node->getChildren())
	{
		GameUtils::pause(child);
	}
}

// A better resume function that resumes recursively
void GameUtils::resume(Node *node)
{
	// If the node is a scene node, resume physics
	if (dynamic_cast<const Scene*>(node) != nullptr)
	{
		Director::getInstance()->getRunningScene()->getPhysicsWorld()->setSpeed(1.0f);
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
	node->addChild(Mouse::claimInstance());
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

void GameUtils::fadeInObject(Node* node, float delay, float duration)
{
	Sequence* sequence = Sequence::create(DelayTime::create(delay), FadeIn::create(duration), nullptr);

	node->setCascadeOpacityEnabled(true);
	node->setOpacity(0);
	node->runAction(sequence);
}

Rect GameUtils::getSceneBounds(Node* node)
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

Rect GameUtils::getSceneBoundsV2(Node* node)
{
	Rect resultRect = node->getBoundingBox();
	Vec2 resultCoords = Vec2(resultRect.getMinX(), resultRect.getMinY());
	Vec2 resultSize = Vec2(resultRect.size.width, resultRect.size.height);

	if (node->getParent() != nullptr)
	{
		resultCoords = node->getParent()->convertToWorldSpace(resultCoords);
	}

	resultRect.setRect(resultCoords.x, resultCoords.y, resultSize.x, resultSize.y);

	return resultRect;
}

bool GameUtils::isVisible(Node* node)
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

bool GameUtils::intersects(Node* node, Vec2 mousePos)
{
	Rect mouseRect = Rect(mousePos.x, mousePos.y, 1.0f, 1.0f);

	if (GameUtils::getSceneBounds(node).intersectsRect(mouseRect))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool GameUtils::intersectsV2(Node* node, Vec2 mousePos)
{
	Rect mouseRect = Rect(mousePos.x, mousePos.y, 1.0f, 1.0f);

	if (GameUtils::getSceneBoundsV2(node).intersectsRect(mouseRect))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool GameUtils::keyExists(ValueMap valueMap, std::string key)
{
	auto pointsIterator = valueMap.find(key);

	if (pointsIterator != valueMap.end())
	{
		return true;
	}

	return false;
}
