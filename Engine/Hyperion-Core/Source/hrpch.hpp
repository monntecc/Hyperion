#pragma once

#include "Runtime/Core/PlatformDetection.hpp"

#ifdef HR_PLATFORM_WINDOWS
#ifndef NOMINMAX
// See github.com/skypjack/entt/wiki/Frequently-Asked-Questions#warning-c4003-the-min-the-max-and-the-macro
#define NOMINMAX
#endif
#endif

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

#include <string>
#include <sstream>
#include <vector>
#include <array>
#include <unordered_map>
#include <unordered_set>

#include "Runtime/Core/Base.hpp"
#include <Runtime/Core/Log.hpp>

#ifdef HR_PLATFORM_WINDOWS
	#include <Windows.h>
#endif // HR_PLATFORM_WINDOWS