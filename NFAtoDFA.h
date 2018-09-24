//
// Created by Patrick on 9/23/2018.
//

#ifndef PROJECT1CSC173_NFATODFA_H
#define PROJECT1CSC173_NFATODFA_H

#include "dfa.h"
#include "nfa.h"
#include "IntHashSet.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

extern int IntHashSettoInteger(IntHashSet set, int NFAstates);

extern IntHashSet IntegertoSubset(int num, int NFAstates);

extern void search(NFA nfa, IntHashSet currentStates, IntHashSet visited, int DFAstatesMax);

extern void setTransitions(NFA nfa, IntHashSet currentStates, IntHashSet visited, int DFAstatesMax);


extern DFA NFAtoDFA(NFA nfa);

#endif //PROJECT1CSC173_NFATODFA_H
