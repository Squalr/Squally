#pragma once

#include "Scenes/Cipher/Components/Blocks/BlockBase.h"

class SubBlock : public BlockBase
{
public:
	static SubBlock* create();

private:
	typedef BlockBase super;
	SubBlock();
	~SubBlock();

	void onEnter() override;
	void initializePositions() override;
};
