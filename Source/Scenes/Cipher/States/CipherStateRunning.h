#pragma once

#include "Scenes/Cipher/States/CipherStateBase.h"

class BlockBase;

class CipherStateRunning : public CipherStateBase
{
public:
	static CipherStateRunning* create();

protected:
	void onBeforeStateEnter(CipherState* cipherState) override;
	void onStateEnter(CipherState* cipherState) override;
	void onStateReload(CipherState* cipherState) override;
	void onStateExit(CipherState* cipherState) override;

private:
	typedef CipherStateBase super;
	CipherStateRunning();
	~CipherStateRunning();

	void performExecuteLoop(std::vector<BlockBase*> blocks, std::function<void()> onExecuteComplete, int index = 0);
};
