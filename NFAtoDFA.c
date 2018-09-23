#include "dfa.h"
#include "nfa.h"
#include "IntHashSet.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

int IntHashSettoInteger(IntHashSet set, int NFAstates){
    char* binary = (char*)malloc(NFAstates*sizeof(char));
    for(int i = 0; i<NFAstates; i++){
        if(IntHashSet_lookup(set, i)){
            binary[i] = "1";
        }
        else{
            binary[i] = "0";
        }
    }
    int num = 0;
    for(int i = 0; i<NFAstates; i++){
        if(binary[i] == 1){
            num+= 1<<i;
        }
    }
    free(binary);
    return num;
}

IntHashSet IntegertoSubset(int num, int NFAstates){ //BE SURE TO FREE IF YOU MAKE A HASHSET WITH THIS
    IntHashSet set = new_IntHashSet(0);
    char* binary = (char*)malloc(NFAstates*sizeof(char));
    for(int i = NFAstates-1; i>=0; i--){
        if((num-1<<i) > 0){
            num = num-1<<i;
            binary[i] = 1;
        }
        else{
            binary[i] = 0;
        }
    }

    for(int i = 0; i<NFAstates; i++){
        if(binary[i] == 1){
            IntHashSet_insert(set, i);
        }
    }
    return set;
}

DFA NFAtoDFA(NFA nfa){
    int NFAstates = NFA_get_size(nfa);
    int DFAstates = 1<<NFAstates;

    DFA dfa = new_DFA(DFAstates);
    for(int setInPowerSet = 0; setInPowerSet<DFAstates; setInPowerSet++){
        for(int ascii = 0; ascii<128; ascii++){
            int src = setInPowerSet;
            int dst = IntHashSettoInteger(get_possible_statesFromChar(nfa, (char) ascii, IntegertoSubset(setInPowerSet, NFAstates)), NFAstates);
            DFA_set_transition(dfa, src, (char) ascii, dst);
        }
    }

    //SET ACCEPTING STATES
    for(int setInPowerSet = 0; setInPowerSet<DFAstates; setInPowerSet++){
        IntHashSet subset = IntegertoSubset(setInPowerSet, NFAstates);
        IntHashSetIterator it = IntHashSet_iterator(subset);
        while(IntHashSetIterator_hasNext(it)){
            int state = IntHashSetIterator_next(it);
            if(NFA_get_accepting(nfa, state)){
                DFA_set_accepting(dfa, setInPowerSet, true);
            }
        }
        IntHashSet_free(subset);
        free(it);
    }

    return dfa;
}