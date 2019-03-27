#pragma once

#include "Scenes/Cipher/States/CipherStateBase.h"

class BlockBase;

class CipherStateUnlocking : public CipherStateBase
{
public:
	static CipherStateUnlocking* create();

protected:
	void onBeforeStateEnter(CipherState* cipherState) override;
	void onStateEnter(CipherState* cipherState) override;
	void onStateReload(CipherState* cipherState) override;
	void onStateExit(CipherState* cipherState) override;

private:
	typedef CipherStateBase super;
	CipherStateUnlocking();
	~CipherStateUnlocking();

	void performUnlockLoop(CipherState* cipherState, std::vector<BlockBase*> inputBlocks, std::vector<BlockBase*> immediateBlocks, std::function<void()> onExecuteComplete, int index = 0);
	void performExecuteLoop(std::vector<BlockBase*> blocks, std::function<void()> onExecuteComplete, int index = 0);
};
