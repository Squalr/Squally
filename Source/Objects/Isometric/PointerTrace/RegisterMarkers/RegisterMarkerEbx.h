#pragma once

#include "Objects/Isometric/PointerTrace/RegisterMarkers/RegisterMarker.h"

class RegisterMarkerEbx : public RegisterMarker
{
public:
	static RegisterMarkerEbx* create();

protected:
	RegisterMarkerEbx();
	~RegisterMarkerEbx();

	int getRegisterIndex() override;

private:
	typedef RegisterMarker super;
};
