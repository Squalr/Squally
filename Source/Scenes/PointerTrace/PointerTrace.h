#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class LayerColor;
}

class PointerTrace : public SmartNode
{
public:
	static PointerTrace* create();

protected:
	PointerTrace();
	~PointerTrace();

private:
	typedef SmartNode super;
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
};
