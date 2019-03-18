#pragma once

#include "Scenes/Cipher/Components/Blocks/BlockBase.h"

class ShrBlock : public BlockBase
{
public:
	static ShrBlock* create();

private:
	typedef BlockBase super;
	ShrBlock();
	~ShrBlock();

	void onEnter() override;
	void initializePositions() override;
};
