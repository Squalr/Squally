#include "GameUtils.h"

std::vector<std::string> GameUtils::getAllAnimationFiles(std::string firstFrameResource)
{
	// Normalize directory seperator
	firstFrameResource = StrUtils::replaceAll(firstFrameResource, "\\", "/");

	size_t extensionIndex = firstFrameResource.find_last_of(".");

	// Extract the base animation name from the provided animation resource (ie HARPY_WALKING_0001.png > HARPY_WALKING)
	// Note: The animations must follow the format of {ANIMATION_BASE}{INDEX}{EXTENSION}, with the index optionally leading w/ zeros
	std::string extensionlessBaseName = firstFrameResource.substr(0, extensionIndex);
	std::string extension = firstFrameResource.substr(extensionIndex, firstFrameResource.size());
	size_t lastIndex = extensionlessBaseName.find_last_not_of("0123456789");
	std::string animationNameBase = extensionlessBaseName.substr(0, lastIndex);

	std::string directoryName = firstFrameResource.substr(0, firstFrameResource.find_last_of("/\\"));

	// These files wont be sorted on the filesystem because strings do not sort like ints -- build an ordered map of int to string
	std::map<int, std::string> orderedAnimationFileMap = std::map<int, std::string>();
	std::vector<std::string> files = FileUtils::getInstance()->listFiles(directoryName);

	for (auto it = files.begin(); it != files.end(); it++)
	{
		std::string fileName = StrUtils::replaceAll(*it, "\\", "/");

		// Check if the file name matches the format of 
		if (StrUtils::startsWith(fileName, animationNameBase, true) && StrUtils::endsWith(fileName, extension, true))
		{
			// Extract the frame number and cast it to an integer
			std::string fileNameNoExtension = fileName.substr(0, fileName.find_last_of("."));
			std::string animationFrameIndex = fileNameNoExtension.substr(fileNameNoExtension.find_last_not_of("0123456789") + 1);

			// Should always be an int, but just in case
			if (StrUtils::isInteger(animationFrameIndex))
			{
				int index = std::stoi(animationFrameIndex);

				// Now that we have the actual index as an integer, store it in our mapping
				orderedAnimationFileMap.insert_or_assign(index, fileName);
			}
		}
	}

	std::vector<std::string> foundAnimations = std::vector<std::string>();

	for (auto it = orderedAnimationFileMap.begin(); it != orderedAnimationFileMap.end(); it++)
	{
		std::string fileName = it->second;

		foundAnimations.push_back(fileName);
	}

	return foundAnimations;
}

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
	if (node == nullptr)
	{
		return;
	}

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

Node* GameUtils::changeParent(Node* node, Node* newParent, bool retainPosition)
{
	Vec2 newPosition = Vec2::ZERO;

	if (node->getParent() != nullptr)
	{
		if (retainPosition)
		{
			Vec2 screenPosition = node->getParent()->convertToWorldSpace(node->getPosition());
			newPosition = newParent->convertToNodeSpace(screenPosition);
		}

		node->retain();
		node->removeFromParent();
	}

	newParent->addChild(node);
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

	resultCoords -= (Camera::getDefaultCamera()->getPosition() - Director::getInstance()->getVisibleSize() / 2.0f);
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

	resultCoords -= (Camera::getDefaultCamera()->getPosition() - Director::getInstance()->getVisibleSize() / 2.0f);
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

bool GameUtils::keyExists(ValueMap* valueMap, std::string key)
{
	auto pointsIterator = valueMap->find(key);

	if (pointsIterator != valueMap->end())
	{
		return true;
	}

	return false;
}
