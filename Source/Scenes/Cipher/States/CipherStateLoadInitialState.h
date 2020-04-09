#pragma once

#include "Scenes/Cipher/States/CipherStateBase.h"

class BlockBase;

class CipherStateLoadInitialState : public CipherStateBase
{
public:
	static CipherStateLoadInitialState* create();

protected:
	CipherStateLoadInitialState();
	virtual ~CipherStateLoadInitialState();
	
	void onBeforeStateEnter(CipherState* cipherState) override;
	void onStateEnter(CipherState* cipherState) override;
	void onStateReload(CipherState* cipherState) override;
	void onStateExit(CipherState* cipherState) override;

private:
	typedef CipherStateBase super;

	void buildSpawnMap();
	void spawnBlocks(CipherState* cipherState);
	void spawnBlock(BlockBase* block, int index, int total);

	std::map<std::string, std::function<void(int, int)>> spawnMap;
};
