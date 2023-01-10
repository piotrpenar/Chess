#include "Chess.h"
#include "Modules/ModuleManager.h"

IMPLEMENT_PRIMARY_GAME_MODULE(FDefaultGameModuleImpl, Chess, "Chess");

/// TODO:
/// Change to references instead of pointers where possible and valid
/// Verify classes for UObject, UProperty macros -if they are not missing or not needed
/// Add Stalemate Detection
/// Add Const wherever possible and logical
