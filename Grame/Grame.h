#pragma once
#include <Grengine.h>

class Grame : public Grengine::Grapplication
{
public:
	Grame();
	void Update(double dt) override final;
	void Render() override final;
};
