#include "InfiniteParallaxNode.h"

InfiniteParallaxNode* InfiniteParallaxNode::create()
{
	InfiniteParallaxNode* node = new InfiniteParallaxNode();

	if (node)
	{
		node->autorelease();
	}
	else
	{
		delete node;
		node = nullptr;
	}

	return node;
}

void InfiniteParallaxNode::updatePosition()
{
	// Get visible size
	Size visibleSize = Director::getInstance()->getVisibleSize();

	// 1. For each child of an parallax node
	for (int i = 0; i < _children.size(); i++)
	{
		Node* node = _children.at(i);

		float nodeX = convertToWorldSpace(node->getPosition()).x;
		float width = node->getContentSize().width;

		// 2. We check whether it is out of the left side of the visible area
		if (nodeX + width < 0)

			// 3. Find PointObject that corresponds to current node
			for (int i = 0; i < _parallaxArray->num; i++)
			{
				PointObject* po = (PointObject*)_parallaxArray->arr[i];

				// If yes increase its current offset on the value of visible width
				if (po->getChild() == node)
				{
					po->setOffset(po->getOffset() + Point(visibleSize.width + node->getContentSize().width, 0));
				}
			}
	}
}
