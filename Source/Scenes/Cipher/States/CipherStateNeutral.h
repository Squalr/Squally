#pragma once

#include "Scenes/Cipher/States/CipherStateBase.h"

class CipherStateNeutral : public CipherStateBase
{
public:
	static CipherStateNeutral* create();

protected:
	void onBeforeStateEnter(CipherState* cipherState) override;
	void onStateEnter(CipherState* cipherState) override;
	void onStateReload(CipherState* cipherState) override;
	void onStateExit(CipherState* cipherState) override;

private:
	typedef CipherStateBase super;
	CipherStateNeutral();
	~CipherStateNeutral();
};
