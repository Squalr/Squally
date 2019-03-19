#pragma once

#include "Scenes/Cipher/Components/Blocks/BlockBase.h"

class MulBlock : public BlockBase
{
public:
	static MulBlock* create(bool isToolBoxItem = false);
	
protected:
	BlockBase* spawn() override;

private:
	typedef BlockBase super;
	MulBlock(bool isToolBoxItem);
	~MulBlock();

	void onEnter() override;
	void initializePositions() override;
};
