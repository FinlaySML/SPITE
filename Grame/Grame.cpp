#include "Grame.h"
#include "RenderSystem.h"
#include <iostream>

//Create the application layer
//See Grapplication.h
Grengine::Grapplication* Grengine::CreateApp(int argc, char** argv)
{
	return new Grame();
}

Grame::Grame()
{
}

void Grame::Update(double dt)
{
	std::cout << "Update " << dt << "\n";
}

void Grame::Render()
{
}
