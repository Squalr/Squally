#pragma once

#include "Scenes/Cipher/Components/Blocks/BlockBase.h"

class MulBlock : public BlockBase
{
public:
	static MulBlock* create();

private:
	typedef BlockBase super;
	MulBlock();
	~MulBlock();

	void onEnter() override;
	void initializePositions() override;
};
