#include "Chess.h"
#include "Modules/ModuleManager.h"

IMPLEMENT_PRIMARY_GAME_MODULE(FDefaultGameModuleImpl, Chess, "Chess");

/// TODO:
/// Adjust namings - Figure, Piece
/// Separate Chessboard and SimulatedChessboard into separate classes. Do this with chess controller aswell.
/// Divide ChessController into separate objects
/// Verify folders and file naming
/// hange to references instead of pointers where possible and valid
/// Verify classes for UObject, UProperty macros -if they are not missing or not needed
/// Add Stalemate Detection
/// Add Const wherever possible and logical
