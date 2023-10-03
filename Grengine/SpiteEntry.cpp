#include "pch.h"

#include "Spite.h"

int main(int argc, char* argv[]) {
    std::unique_ptr<Spite::Core> engine(new Spite::Core(argc, argv));

    return engine->Run();
}

//We're probably on Windows!
//Let's just handle everything through Main, just in case
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {

    return main(__argc, __argv);
}