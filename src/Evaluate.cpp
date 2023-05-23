#include "Evaluate.h"

#include <bits/stdc++.h>

bool check_file_isolated(BoardConfig config, int fileToCheck, PlaySide side) {
	if (side == WHITE) {
		for (int i = 1; i <= 8; i++) {
			if (config.config[i][fileToCheck] == WHITE_EN_PAS || config.config[i][fileToCheck] == WHITE_PAWN) {
				return false;
			}
		}
	} else {
		for (int i = 1; i <= 8; i++) {
			if (config.config[i][fileToCheck] == BLACK_EN_PAS || config.config[i][fileToCheck] == BLACK_PAWN) {
				return false;
			}
		}
	}

	return true;
}

double evaluate_basic(BoardConfig config, bool canCastle, int possible_moves, PlaySide side) {
	double score = 0;

	for (int i = 1; i <= TABLE_SIZE; i++) {
		for (int j = 1; j <= TABLE_SIZE; j++) {
			if (config.config[i][j] != NO_PIECE) {
				switch (config.config[i][j])
				{
				case WHITE_PAWN:
				case WHITE_EN_PAS:
					score += PAWN_S;

					bool isolatedRight, isolatedLeft;
					if (j - 1 >= 1) {
						isolatedLeft = check_file_isolated(config, j - 1, WHITE);
					}
					if (j + 1 <= 8) {
						isolatedRight = check_file_isolated(config, j + 1, WHITE);
					}

					if (isolatedLeft && isolatedRight) {
						score -= ISOLATED_PAWNS_S;
					}
					break;
				case BLACK_PAWN:
				case BLACK_EN_PAS:
					score -= PAWN_S;
					break;
				case WHITE_ROOK:
					score += ROOK_S;
					break;
				case BLACK_ROOK:
					score -= ROOK_S;
					break;
				case WHITE_KNIGHT:
					score += KNIGHT_S;
					break;
				case BLACK_KNIGHT:
					score -= KNIGHT_S;
					break;
				case WHITE_BISHOP:
					score += BISHOP_S;
					break;
				case BLACK_BISHOP:
					score -= BISHOP_S;
					break;
				case WHITE_QUEEN:
					score += QUEEN_S;
					break;
				case BLACK_QUEEN:
					score -= QUEEN_S;
					break;
				case WHITE_KING:
					score += KING_S;
					break;
				case BLACK_KING:
					score -= KING_S;
					break;
				case P_WHITE_QUEEN:
					score += P_QUEEN_S;
					break;
				case P_BLACK_QUEEN:
					score -= P_QUEEN_S;
					break;
				case P_WHITE_KNIGHT:
					score += P_KNIGHT_S;
					break;
				case P_BLACK_KNIGHT:
					score -= P_KNIGHT_S;
					break;
				default:
					break;
				}
			}
		}
	}

	if (canCastle) {
		score += CASTLE_S;
	}

	score += MOBILITY_S * possible_moves;

	return score;
}

double pawnPosition(BoardConfig config, int i, int j) {
	double pawnScore = 0;

	if (3 <= i && i <= 6 && 4 <= j && j <= 6) {
		pawnScore += CENTER_PAWN;
	}

	/* check if a pawn is supported by another pawn */
	if (config.config[i + 1][j - 1] == WHITE_EN_PAS ||
		config.config[i + 1][j + 1] == WHITE_EN_PAS ||
		config.config[i + 1][j - 1] == WHITE_PAWN ||
		config.config[i + 1][j + 1] == WHITE_PAWN) {
			pawnScore += PAWN_STRUCTURE;
		}

	if (config.config[i - 1][j - 1] == WHITE_EN_PAS ||
		config.config[i - 1][j + 1] == WHITE_EN_PAS ||
		config.config[i - 1][j - 1] == WHITE_PAWN ||
		config.config[i - 1][j + 1] == WHITE_PAWN) {
			pawnScore += PAWN_STRUCTURE;
		}

	/* check if a pawn supports another pawn */
	if (config.config[i + 1][j - 1] == BLACK_EN_PAS ||
		config.config[i + 1][j + 1] == BLACK_EN_PAS ||
		config.config[i + 1][j - 1] == BLACK_PAWN ||
		config.config[i + 1][j + 1] == BLACK_PAWN) {
			pawnScore += PAWN_STRUCTURE;
		}

	if (config.config[i - 1][j - 1] == BLACK_EN_PAS ||
		config.config[i - 1][j + 1] == BLACK_EN_PAS ||
		config.config[i - 1][j - 1] == BLACK_PAWN ||
		config.config[i - 1][j + 1] == BLACK_PAWN) {
			pawnScore += PAWN_STRUCTURE;
		}

	return pawnScore;
}

double pawnControl(BoardConfig config) {
	double pawnStructureScore = 0;

	for (int i = 1; i <= TABLE_SIZE; i++) {
		for (int j = 1; j <= TABLE_SIZE; j++) {
			switch(config.config[i][j]) {
				case WHITE_EN_PAS:
				case WHITE_PAWN:
					pawnStructureScore += pawnPosition(config, i, j);
					break;
				case BLACK_EN_PAS:
				case BLACK_PAWN:
					pawnStructureScore -= pawnPosition(config, i, j);
					break;
				default:
					break;
			}
		}
	}

	return pawnStructureScore;
}

double knightsEarly(BoardConfig config) {
	double knightsEarlyScore = 0;

	for (int i = 1; i <= TABLE_SIZE; i++) {
		for (int j = 1; j <= TABLE_SIZE; j++) {
			switch(config.config[i][j]) {
				case WHITE_KNIGHT:
					if ((i == 3 && j == 3) || (i == 3 && j == 6)) {
						knightsEarlyScore += KNIGHT_EARLY_S;
					}
					break;
				case BLACK_KNIGHT:
					if ((i == 6 && j == 3) || (i == 6 && j == 6)) {
						knightsEarlyScore -= KNIGHT_EARLY_S;
					}
					break;
				default:
					break;
			}
		}
	}

	return knightsEarlyScore;
}

double bishopControl(BoardConfig config) {
	double bishopControlScore = 0;

	for (int i = 1; i <= TABLE_SIZE; i++) {
		for (int j = 1; j <= TABLE_SIZE; j++) {
			switch(config.config[i][j]) {
				case WHITE_BISHOP:
					if (3 <= i && i <= 6 && 3 <= j && j <= 6) {
						bishopControlScore += BISHOP_CONTROL_S;
					}
					break;
				case BLACK_BISHOP:
					if (3 <= i && i <= 6 && 3 <= j && j <= 6) {
						bishopControlScore -= BISHOP_CONTROL_S;
					}
					break;
				default:
					break;
			}
		}
	}

	return bishopControlScore;
}

double rookControl(BoardConfig config) {
	double rookControlScore = 0;

	for (int i = 1; i <= TABLE_SIZE; i++) {
		for (int j = 1; j <= TABLE_SIZE; j++) {
			switch(config.config[i][j]) {
				case WHITE_ROOK:
					if (3 <= i && i <= 6 && 2 <= j && j <= 7) {
						rookControlScore += ROOK_CONTROL_S;
					}
					break;
				case BLACK_ROOK:
					if (3 <= i && i <= 6 && 2 <= j && j <= 7) {
						rookControlScore -= ROOK_CONTROL_S;
					}
					break;
				default:
					break;
			}
		}
	}

	return rookControlScore;
}

double evaluate_early(BoardConfig config, bool canCastle, int possibleMoves, PlaySide side) {
	double score = evaluate_basic(config, canCastle, possibleMoves, side);
	score += pawnControl(config);
	score += knightsEarly(config);
	return score;
}

double evaluate_late(BoardConfig config, bool canCastle, int possibleMoves, PlaySide side) {
	return 0;
}