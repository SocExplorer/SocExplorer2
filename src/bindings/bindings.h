#pragma once
#define QT_ANNOTATE_ACCESS_SPECIFIER(a) __attribute__((annotate(#a)))

#include "../SocExplorerObject.hpp"
#include "../Workspace.hpp"
#include "../Soc/SocModule.hpp"
#include "../Soc/Soc.hpp"
#include "../Factory/SocExplorerFactory.hpp"
#include "PySocModule.hpp"
