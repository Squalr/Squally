#include "Utils.h"

std::string Utils::HexAddressOf(void* address)
{
	std::stringstream stream;

	// Convert to hex
	stream << std::hex << (int)(address);
	std::string hexAddress = stream.str();

	// Convert to upper
	std::transform(hexAddress.begin(), hexAddress.end(), hexAddress.begin(), ::toupper);

	return hexAddress;
}

void Utils::AccelerateParticles(ParticleSystem* particleSystem, float duration)
{
	const float step = 0.0166660007;

	particleSystem->start();

	for (float currentDuration = 0.0f; currentDuration < duration; currentDuration += step)
	{
		particleSystem->update(step);
	}
}

void Utils::FadeInObject(Node* node, float delay, float duration)
{
	Sequence* sequence = Sequence::create(DelayTime::create(delay), FadeIn::create(duration), nullptr);

	node->setCascadeOpacityEnabled(true);
	node->setOpacity(0);
	node->runAction(sequence);
}

Rect Utils::GetSceneBounds(Node* node)
{
	Rect resultRect = node->getBoundingBox();
	Vec2 resultCoords = Vec2(resultRect.getMinX() - resultRect.size.width / 2, resultRect.getMinY() - resultRect.size.height / 2);
	Vec2 resultSize = Vec2(resultRect.size.width, resultRect.size.height);

	while (node->getParent() != nullptr && dynamic_cast<const Scene*>(node->getParent()) == nullptr)
	{
		resultCoords = node->getParent()->convertToWorldSpace(resultCoords);
		node = node->getParent();
	}

	resultRect.setRect(resultCoords.x, resultCoords.y, resultSize.x, resultSize.y);

	return resultRect;
}

bool Utils::Intersects(Node* node, Vec2 mousePos)
{
	Rect mouseRect = Rect(mousePos.x, mousePos.y, 1.0f, 1.0f);

	if (Utils::GetSceneBounds(node).intersectsRect(mouseRect))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Utils::KeyExists(ValueMap valueMap, std::string key)
{
	auto pointsIterator = valueMap.find(key);

	if (pointsIterator != valueMap.end())
	{
		return true;
	}

	return false;
}
