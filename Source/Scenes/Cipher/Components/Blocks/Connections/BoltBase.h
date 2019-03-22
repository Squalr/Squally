#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Sprite;
}

class ClickableNode;
class Connection;

class BoltBase : public SmartNode
{
public:

protected:
	BoltBase();
	~BoltBase();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

	Connection* connection;

private:
	typedef SmartNode super;

	ClickableNode* connectButton;
	bool isCreatingConnection;
	bool isInClickCreateMode;
};
