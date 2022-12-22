// Copyright Epic Games, Inc. All Rights Reserved.

#include "Chess.h"
#include "Modules/ModuleManager.h"

IMPLEMENT_PRIMARY_GAME_MODULE( FDefaultGameModuleImpl, Chess, "Chess" );

/// TODO:
/// 1. Adjust namings - Figure, Piece
/// 2. Divide ChessController into separate objects
/// 3. Verify folders and file naming
/// 4. Change to references instead of pointers where possible and valid
/// 5. Verify classes for UObject, UProperty macros -if they are not missing or not needed
/// 6. Cleanup Header files and organise them
/// 7. Add Castling
/// 8. Add Pawn Promotion
/// 9. Add En Passant
/// 10. Add Stalemate Detection