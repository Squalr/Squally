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
	virtual void setConnection(Connection* connection);

protected:
	BoltBase();
	~BoltBase();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	virtual void onConnectionUpdated();

	Connection* connection;
	ClickableNode* connectButton;
	bool inputDebug;

private:
	typedef SmartNode super;

	bool isCreatingConnection;
};
