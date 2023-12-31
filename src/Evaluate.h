#ifndef EVALUATE_H
#define EVALUATE_H

#include "BoardHelpers.h"
#include "PlaySide.h"
#include "MoveNode.h"

#define DOUBLE_PAWNS_S -0.5
#define ISOLATED_PAWNS_S -0.5
#define KNIGHT_EARLY_S 1.5
#define ATTACK_NEAR_KING_S 1.5
#define MOBILITY_S 0.05
#define BISHOP_CONTROL_S 1
#define ROOK_CONTROL_S 1.5
#define KING_S 1000.0
#define PAWN_SHIELD_S 0.1
#define PAWN_STORM_S 0.05

enum PieceScore {
  PAWN_S = 1, ROOK_S = 5,
  KNIGHT_S = 3, BISHOP_S = 3,
  QUEEN_S = 9,
  P_ROOK_S = 0, P_KNIGHT_S = 6,
  P_BISHOP_S = 0, P_QUEEN_S = 17,
  CASTLE_S = 3, CENTER_PAWN = 2,
  PAWN_STRUCTURE = 1, KING_CHECK_S = -1
};

bool checkFileIsolated(BoardConfig config, int fileToCheck, PlaySide side);

double pawnPosition(BoardConfig config, int i, int j);

double pawnControl(BoardConfig config);

double knightsEarly(BoardConfig config);

double bishopControl(BoardConfig config);

double rookControl(BoardConfig config);

double evaluateBasic(BoardConfig config, bool canCastle, int possible_moves, PlaySide side);

double evaluateEarly(BoardConfig config, bool canCastle, int possible_moves, PlaySide side, PlaySide engineSide);

double checkKingAttacked(BoardConfig config, PlaySide side);

double checkPawnShield(BoardConfig config, PlaySide side);

double checkPawnStorm(BoardConfig config, PlaySide side);

double evaluateLate(BoardConfig config, bool canCastle, int possible_moves, PlaySide side, PlaySide engineSide);

#endif