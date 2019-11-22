#pragma once

#include "Scenes/Cipher/Components/CipherComponentBase.h"

namespace cocos2d
{
	class Sprite;
}

class ClickableNode;
class Connection;

class BoltBase : public CipherComponentBase
{
public:
	virtual void setConnection(Connection* connection);

protected:
	BoltBase();
	~BoltBase();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void onAnyStateChange(CipherState* cipherState) override;
	virtual void onConnectionUpdated();

	Connection* connection;
	ClickableNode* connectButton;
	bool inputDebug;

private:
	typedef CipherComponentBase super;

	bool isCreatingConnection;
};
