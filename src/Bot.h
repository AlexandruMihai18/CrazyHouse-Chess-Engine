#ifndef BOT_H
#define BOT_H
#include <bits/stdc++.h>

#include "MoveNode.h"
#include "Evaluate.h"

#define INF (int)(1 << 30)
#define EARLY_DEPTH 4
#define LATE_DEPTH 4
#define EARLY_TIMESTAMP 8

class Bot {
 private:
  static const std::string BOT_NAME;

 public:
  /* Declare custom fields below */

  /**
   * Game board with index starting from 1 for easier movement
   * management (rows - 1 to 8, columns - A to H)
   * White King - E1
   * Black King - E8
   */
  MoveNode root;
  PlaySide enemySide;
  bool threeRepeatedConfigs;
  int counterMoves;

  /* Past table configs */
  std::vector<BoardConfig> pastConfigs;

  int timestamp;

  /* Declare custom fields above */
  Bot();

  /**
   * Record move (either by enemy in normal mode, or by either side
   * in force mode) in custom structures
   * @param move received move
   * @param sideToMode side to move
   */
  void recordMove(Move* move, PlaySide sideToMove);

  /**
   * Calculates next move, in response to enemyMove
   * @param enemyMove the enemy's last move
   *                  null if this is the opening move, or previous
   *                  move has been recorded in force mode
   * @return your move
   */
  Move* calculateNextMove();

  /* select specific player side piece from a generic piece */
  PlaySidePiece selectPiece(Piece piece, PlaySide mySide, bool type);
  
  /* convert to regular piece an en passant pawn at the specified coords */
  PlaySidePiece convertRegularPiece(int &x, int &y);

  /* copy the current config in the pastConfigs vector */
  void copyCurrentConfig();

  /* check for repeated configs in the pastConfigs vector */
  bool checkRepeatedConfigs();

  void showBoard();

  void showBoard2(MoveNode move);

  static std::string getBotName();

  double alphaBetaEarly(PlaySide myside, PlaySide enemyside, int depth, double alpha, double beta, MoveNode current, MoveNode &bestMove, int &counter);

  double alphaBetaLate(PlaySide myside, PlaySide enemyside, int depth, double alpha, double beta, MoveNode current, MoveNode &bestMove, int &counter);
};

#endif
