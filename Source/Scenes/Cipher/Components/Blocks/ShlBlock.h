#pragma once

#include "Scenes/Cipher/Components/Blocks/BlockBase.h"

class ShlBlock : public BlockBase
{
public:
	static ShlBlock* create();

private:
	typedef BlockBase super;
	ShlBlock();
	~ShlBlock();

	void onEnter() override;
	void initializePositions() override;
};
