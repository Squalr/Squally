#pragma once

#include "Engine/GlobalScene.h"

class Cipher;

class CipherScene : public GlobalScene
{
public:
	static void registerGlobalScene();

protected:
	CipherScene();
	~CipherScene();

private:
	typedef GlobalScene super;
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

	Cipher* cipher;

	static CipherScene* instance;
};
