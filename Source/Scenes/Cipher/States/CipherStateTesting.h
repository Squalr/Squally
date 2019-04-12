#pragma once

#include "Scenes/Cipher/States/CipherStateBase.h"

class BlockBase;

class CipherStateTesting : public CipherStateBase
{
public:
	static CipherStateTesting* create();

protected:
	void onBeforeStateEnter(CipherState* cipherState) override;
	void onStateEnter(CipherState* cipherState) override;
	void onStateReload(CipherState* cipherState) override;
	void onStateExit(CipherState* cipherState) override;

private:
	typedef CipherStateBase super;
	CipherStateTesting();
	~CipherStateTesting();

	void performExecuteLoop(std::vector<BlockBase*> blocks, std::function<void()> onExecuteComplete, int index = 0);
};
