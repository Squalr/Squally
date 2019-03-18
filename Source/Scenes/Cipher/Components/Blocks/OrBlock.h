#pragma once

#include "Scenes/Cipher/Components/Blocks/BlockBase.h"

class OrBlock : public BlockBase
{
public:
	static OrBlock* create();

private:
	typedef BlockBase super;
	OrBlock();
	~OrBlock();

	void onEnter() override;
	void initializePositions() override;
};
