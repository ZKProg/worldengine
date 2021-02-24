#include "pch.h"

#include "contextglsdl.hpp"
#include "settingsmixin.hpp"

#ifdef __linux
#define RUN_TESTS
#endif

#ifdef RUN_TESTS
#include "core_tests.hpp"
#endif

int main(int argc, char **argv)
{
  std::cout << "Will I run the tests?!" << std::endl;
#ifdef RUN_TESTS
  std::cout << "YES I WILL" << std::endl;
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
