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
