#pragma once

#include "Objects/Isometric/PointerTrace/RegisterMarkers/RegisterMarker.h"

class RegisterMarkerEbp : public RegisterMarker
{
public:
	static RegisterMarkerEbp* create();

protected:
	RegisterMarkerEbp();
	~RegisterMarkerEbp();

	int getRegisterIndex() override;

private:
	typedef RegisterMarker super;
};
