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

bool Utils::Intersects(Node* node, Vec2 mousePos)
{
	Rect mouseRect = Rect(mousePos.x, mousePos.y, 1.0f, 1.0f);

	Vec2 origin = Director::getInstance()->getRunningScene()->convertToWorldSpace(Vec2(node->getBoundingBox().origin.x, node->getBoundingBox().origin.y));
	Rect nodeRect = Rect(origin.x - node->getContentSize().width / 2, origin.y - node->getContentSize().height / 2, node->getContentSize().width, node->getContentSize().height);

	if (nodeRect.intersectsRect(mouseRect))
	{
		return true;
	}
	else
	{
		return false;
	}
}
