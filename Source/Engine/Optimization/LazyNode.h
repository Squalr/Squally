#pragma once
#include <functional>

#include "cocos/2d/CCNode.h"

template <class T>
class LazyNode : public cocos2d::Node
{
public:
	static LazyNode* create(std::function<T*()> createFunc)
	{
		LazyNode* instance = new LazyNode(createFunc);

		instance->autorelease();

		return instance;
	}

	bool isBuilt() { return lazyInstance != nullptr; }

	T* lazyGet()
	{
		if (lazyInstance == nullptr)
		{
			lazyInstance = createFunc();

			this->addChild(lazyInstance);
		}

		return lazyInstance;
	}

protected:
	LazyNode(std::function<T*()> createFunc)
	{
		this->lazyInstance = nullptr;
		this->createFunc = createFunc;
	}

	virtual ~LazyNode() = default;
	
private:
	typedef cocos2d::Node super;
	
	// Hide methods that we do not want available
	using super::setOpacity;
	using super::setVisible;
	using super::setPosition;
	using super::setPositionX;
	using super::setPositionY;
	using super::setScale;
	using super::setScaleX;
	using super::setScaleY;
	using super::setScaleZ;
	using super::setAnchorPoint;
	using super::setRotation;
	using super::getOpacity;
	using super::isVisible;
	using super::getPosition;
	using super::getPositionX;
	using super::getPositionY;
	using super::getScale;
	using super::getScaleX;
	using super::getScaleY;
	using super::getScaleZ;
	using super::getAnchorPoint;
	using super::getRotation;

	std::function<T*()> createFunc;
	T* lazyInstance;
};
