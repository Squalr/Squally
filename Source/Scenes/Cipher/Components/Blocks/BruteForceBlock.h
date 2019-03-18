#pragma once

#include "Scenes/Cipher/Components/Blocks/BlockBase.h"

class BruteForceBlock : public BlockBase
{
public:
	static BruteForceBlock* create();

private:
	typedef BlockBase super;
	BruteForceBlock();
	~BruteForceBlock();

	void onEnter() override;
	void initializePositions() override;
};
