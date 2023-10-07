#include "pch.h"
#include "Internal.h"

int main(int argc, char* argv[]) {
    return Spite::Internal::ExecuteGame(argc, argv);
}

//We're probably on Windows!
//Let's just handle everything through Main, just in case
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {

    return main(__argc, __argv);
}