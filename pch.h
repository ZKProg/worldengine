#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <chrono>
#include <memory>
#include <string>
#include <sstream>
#include <thread>
#include <fstream>
#include <regex>
#include <cmath>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_net.h>
#include <SDL2/SDL_ttf.h>

#include <GL/glew.h>
#include <GL/gl.h>

#ifdef __linux
	#include <gtest/gtest.h>
	#include <gmock/gmock.h>
#endif // linux

#ifdef __win32
	#include "stdafx.h"
#endif


//#include <boost/asio.hpp>
#include <boost/range/adaptor/indexed.hpp>



