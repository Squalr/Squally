#pragma once

#include "Scenes/Cipher/Components/Blocks/BlockBase.h"

class DivBlock : public BlockBase
{
public:
	static DivBlock* create();

private:
	typedef BlockBase super;
	DivBlock();
	~DivBlock();

	void onEnter() override;
	void initializePositions() override;
};
