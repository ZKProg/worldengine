#include "pch.h"

#include "contextglsdl.hpp"
#include "settingsmixin.hpp"

// #define RUN_TESTS

#ifdef RUN_TESTS
    #include "objparser_tests.hpp"
#endif

int main (int argc, char **argv)
{
#ifdef RUN_TESTS
    ::testing::InitGoogleTest(&argc, argv);
    RUN_ALL_TESTS();
#endif

    std::cout << "World Engine 0.1 launching..." << std::endl;
    std::unique_ptr<SettingsMixin> mixin(new SettingsMixin);

    if (mixin->m_kV["window"]["backend"] == "sdlgl")
    {
        std::cout << "Rendering backend selected: SDL2/OpenGL" << std::endl;
        ContextGLSDL context(std::move(mixin));
        context.run();
    }
    else
    {
        std::cout << "No valid rendering backend selected." << std::endl;
    }
    
    return 0;
}