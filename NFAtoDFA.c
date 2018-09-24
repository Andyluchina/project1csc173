#include "dfa.h"
#include "nfa.h"
#include "IntHashSet.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

int IntHashSettoInteger(IntHashSet set, int NFAstates){ //HELPER METHOD to switch a hash set to integer value of the 2^n possible subsets
    char* binary = (char*)malloc(NFAstates*sizeof(char));
    for(int i = 0; i<NFAstates; i++){
        if(IntHashSet_lookup(set, i)){
            binary[i] = '1';
        }
        else{
            binary[i] = '0';
        }
    }
    int num = 0;
    for(int i = 0; i<NFAstates; i++){
        if(binary[i] == '1'){
            int binaryPart =  ((unsigned) 1<< (unsigned) i);
            num+=binaryPart;
        }
    }
   // printf("the binary string: %s \n", binary);
    free(binary);
   // printf("IntHashSettoInteger Method    THE NUMBER: %d ", num);
   // printf("  THE HASHSET ORIGINAL: ");
   // printf("%s", IntHashSet_toString(set));
    //printf("\n");


    return num;
}

IntHashSet IntegertoSubset(int num, int NFAstates){ //Helper method to take integer from 1 to 2^n subset and return the subset
    IntHashSet set = new_IntHashSet(NFAstates);
    char* binary = (char*)malloc(NFAstates*sizeof(char));
    for(int i = NFAstates-1; i>=0; i--){
        int binP = (unsigned) (num)>> (unsigned) i;
        if(( binP > 0)){
            int binEx = (unsigned)1<<(unsigned)i;
            num = num -  binEx;
            binary[i] = '1';
        }
        else{
            binary[i] = '0';
        }
    }

    for(int i = 0; i<NFAstates; i++){
        if(binary[i] == '1'){
            IntHashSet_insert(set, i);
        }
    }
//    printf("INTHASHSET: ");
//    printf("\n");

    free(binary);
    return set;
}

void search(NFA nfa, IntHashSet currentStates, IntHashSet visited, int DFAstatesMax){
    IntHashSet newCurrentStates;
    for(int ascii = 0; ascii<128; ascii++){
        IntHashSet_insert(visited, IntHashSettoInteger(currentStates, DFAstatesMax)); //set currentStates to visited!
        newCurrentStates = get_possible_statesFromChar(nfa, (char) ascii, currentStates);
        if(! IntHashSet_lookup(visited, IntHashSettoInteger(newCurrentStates, DFAstatesMax))){

//            IntHashSet_free(currentStates);
            search(nfa, newCurrentStates, visited, DFAstatesMax);
        }
        else{
//            IntHashSet_free(currentStates);
        }
    }
}

void setTransitions(NFA nfa, IntHashSet currentStates, IntHashSet visited, DFA dfa, int* toState, int toStateLength){
    IntHashSet newCurrentStates;
    int DFAstatesMax= DFA_get_size(dfa);
    for(int ascii = 0; ascii<128; ascii++){
        IntHashSet_insert(visited, IntHashSettoInteger(currentStates, DFA_get_size(dfa))); //set currentStates to visited!
        newCurrentStates = get_possible_statesFromChar(nfa, (char) ascii, currentStates);
        int src = IntHashSettoInteger(currentStates, NFA_get_size(nfa));
        int dst = IntHashSettoInteger(newCurrentStates, NFA_get_size(nfa));

        for(int i = 0; i<toStateLength ; i++){
           // printf("toState[i] = %d, i = %d, src = %d, dst = %d \n", toState[i], i, src, dst);
            if(toState[i] == src){
                src = i;
               // printf("src: %d \n", src);
            }
            if(toState[i] == dst){
                dst =i;
              //  printf("dst: %d \n",  dst);

            }
        }
        DFA_set_transition(dfa, src, (char) ascii, dst);
        if(! IntHashSet_lookup(visited, IntHashSettoInteger(newCurrentStates, DFAstatesMax))){
//            IntHashSet_free(currentStates);

            setTransitions(nfa, newCurrentStates, visited, dfa, toState, toStateLength);
        }
        else{
//            IntHashSet_free(currentStates);
        }
    }
}

DFA NFAtoDFA(NFA nfa){
    int NFAstates = NFA_get_size(nfa);
    int DFAstatesMax = (unsigned) 1<< (unsigned) NFAstates;
    IntHashSet currentStates = new_IntHashSet(NFAstates);
    IntHashSet  visited = new_IntHashSet(DFAstatesMax);
    IntHashSet_insert(currentStates, 0);

    search(nfa, currentStates, visited, DFAstatesMax);

    int sizeDFA = 0;

    //get size
    IntHashSetIterator it = IntHashSet_iterator(visited);
    while(IntHashSetIterator_hasNext(it)) {
        IntHashSetIterator_next(it);
        sizeDFA++;
    }
    free(it);

    //set toState
    int toState[sizeDFA];
    int i = 0;
    IntHashSetIterator it2 = IntHashSet_iterator(visited);
    while(IntHashSetIterator_hasNext(it2)) {
        int elem = IntHashSetIterator_next(it2);
        toState[i] =  elem;
        i++;
    }
    free(it2);
    int toStateLength = sizeof(toState)/sizeof(int);
   // printf("size of toState/size of int: %d \n", toStateLength);
    DFA dfa = new_DFA(sizeDFA);

    IntHashSet visitedTransitions = new_IntHashSet(NFAstates);
    setTransitions(nfa, currentStates, visitedTransitions, dfa, toState, toStateLength);



//    DFA dfa = new_DFA(DFAstates);
//    DFA_set_transition(dfa, src, (char) ascii, dst);


//
    //SET ACCEPTING STATES
    for(int k = 0; k<toStateLength; k++){
        IntHashSet subset = IntegertoSubset(toState[k], NFAstates);
        IntHashSetIterator it3 = IntHashSet_iterator(subset);
        while(IntHashSetIterator_hasNext(it3)){
            int state = IntHashSetIterator_next(it3);
            if(NFA_get_accepting(nfa, state)){
                DFA_set_accepting(dfa, k, true);
            }
        }
        IntHashSet_free(subset);
        free(it3);
    }
//
    free(toState);
    IntHashSet_free(visited);
    IntHashSet_free(visitedTransitions);
    return dfa;
}