#ifndef PCH_H
#define PCH_H

#include "framework.h"
#include "kernelx.h"

#include "CoreWindowWrapperX.h"
#include "ICoreWindowX.h"

#include "../src/detours.h"

#include <intrin.h>
#include <winternl.h>
#include <cstdint>
#include <cstdlib>
#include <roapi.h>
#include <wrl.h>
#include <string>
#include <string_view>
#include <__msvc_string_view.hpp>

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;

#endif //PCH_H