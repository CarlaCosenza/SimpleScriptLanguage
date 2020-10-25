#include <stdio.h>
#include <vector>

#include "naoTerminais.h"

vector <int> NaoTerminaisOperator::ruleLeftTokens = {P, LDE, LDE, DE, DE, T, T, T, T, T, DT, DT, DT, DC, DC, DF, LP, LP, B, LDV, LDV, LS, LS, DV, LI, LI, S, S, U, U, M, M, M, M, M, M, M, E, E, E, L, L, L, L, L, L, L, R, R, R, Y, Y, Y, F, F, F, F, F, F, F, F, F, F, F, F, F, F, LE, LE, LV, LV, LV, IDD, IDU, ID1, TRUE1, FALSE1, CHR, STR, NUM, NB, MF, MC, NF, MT, ME, MW};

vector <int> NaoTerminaisOperator::ruleNumberOfTokens = {1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 9, 8, 4, 5, 3, 10, 5, 3, 4, 2, 1, 2, 1, 5, 3, 1, 1, 1, 6, 9, 9, 7, 8, 2, 4, 2, 2, 3, 3, 1, 3, 3, 3, 3, 3, 3, 1, 3, 3, 1, 3, 3, 1, 1, 2, 2, 2, 2, 3, 5, 2, 2, 1, 1, 1, 1, 1, 3, 1, 3, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0};
