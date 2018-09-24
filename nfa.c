
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "nfa.h"
#include "IntHashSet.h"
#include "Set.h"

struct NFA{
    int startState;
    IntHashSet** transition;
    bool* acceptingStates;
    int states;
};

/**
 * Allocate and return a new NFA containing the given number of states.
 */
NFA new_NFA(int nstates) {
    struct NFA *newNFA = (struct NFA *) malloc(sizeof(struct NFA));
    newNFA->startState = 0; //was equal to 0
    newNFA->states = nstates;
    newNFA->acceptingStates = (bool*) calloc((size_t) nstates, sizeof(bool)); //I have no clue what (size_t) is but clion said to use it for signed values of type in
    for(int i=0; i< sizeof(newNFA->acceptingStates)/nstates; i++){
        newNFA->acceptingStates[i]=false;
    }

    newNFA->transition = (IntHashSet**) malloc(128*sizeof(IntHashSet*));
    for (int i = 0; i < 128; i++) {
        newNFA->transition[i] = (IntHashSet*)malloc(nstates*sizeof(IntHashSet));
    }

    for(int i=0; i<128; i++){
        for(int j=0; j<nstates; j++){
            newNFA->transition[i][j] =new_IntHashSet(newNFA->states);
        }
    }

    return newNFA;
}
/**
 * Free the given NFA.
 */
void NFA_free(NFA nfa){
//freed
    for (int i = 0; i < 128; i++)
    {
        free(nfa->transition[i]);
    }
    printf("free1");

    free(nfa->transition);
//    nfa->transition = NULL;
    free(nfa->acceptingStates);
    free(nfa);

//    free(dfa->transition);
//    dfa->transition = NULL;
//    dfa->acceptingStates = NULL;
//    free(dfa->acceptingStates);
//    dfa->acceptingStates = NULL;
//    free(dfa);
}

/**
 * Return the number of states in the given NFA.
 */
int NFA_get_size(NFA nfa){
    return nfa->states;
}

/**
 * Return the set of next states specified by the given NFA's transition
 * function from the given state on input symbol sym.
 */
IntHashSet NFA_get_transitions(NFA nfa, int state, char sym){
    return nfa->transition[(int)sym][state];
}

/**
 * For the given NFA, add the state dst to the set of next states from
 * state src on input symbol sym.
 */
void NFA_add_transition(NFA nfa, int src, char sym, int dst){
    //printf("%s \n", IntHashSet_toString(nfa->transition[(int)sym][src]));
    IntHashSet_insert((nfa->transition[(int)sym][src]), dst);
    //printf("%s \n", IntHashSet_toString(nfa->transition[(int)sym][src]));
}

/**
 * Add a transition for the given NFA for each symbol in the given str.
 */
void NFA_add_transition_str(NFA nfa, int src, char *str, int dst){
    for(int i=0; i<strlen(str); i++){
        NFA_add_transition(nfa, src, str[i], dst);
    }
}

/**
 * Add a transition for the given NFA for each input symbol.
 */
void NFA_add_transition_all(NFA nfa, int src, int dst){
    for(int i=0; i<128; i++){
        IntHashSet_insert(nfa->transition[i][src],dst);
    }
}

/**
 * Set whether the given NFA's state is accepting or not.
 */
void NFA_set_accepting(NFA nfa, int state, bool value){
    nfa->acceptingStates[state]=value;
}

/**
 * Return true if the given NFA's state is an accepting state.
 */
bool NFA_get_accepting(NFA nfa, int state){
    return nfa->acceptingStates[state];
}

/**
 * Run the given NFA on the given input string, and return true if it accepts
 * the input, otherwise false.
 */
bool NFA_execute(NFA nfa, char *input){
    IntHashSet possible = new_IntHashSet(nfa->states);
    IntHashSet_insert(possible, nfa->startState);
    possible = get_possible_states(nfa, input, possible);

    IntHashSetIterator it = IntHashSet_iterator(possible);

    while(IntHashSetIterator_hasNext(it)) {
        if (NFA_get_accepting(nfa, IntHashSetIterator_next(it))){
            IntHashSet_free(possible);
            return true;
        }
    }
    IntHashSet_free(possible);
    return false;
}


IntHashSet get_possible_states(NFA nfa, char* input, IntHashSet currentStates){
    if((input == NULL) || (input[0] == '\0')){
       // free(input);
        return currentStates;
    }
    IntHashSet possible = new_IntHashSet(nfa->states);
    IntHashSetIterator it = IntHashSet_iterator(currentStates);
    while(IntHashSetIterator_hasNext(it)) {
        int character = (int) input[0];
        int state = IntHashSetIterator_next(it);
        IntHashSet_union(possible, nfa->transition[character][state]);
    }
    free(it);
    IntHashSet_free(currentStates);
    return get_possible_states(nfa, input+1, possible);
}

IntHashSet get_possible_statesFromChar(NFA nfa, char input, IntHashSet currentStates){
    IntHashSet possible = new_IntHashSet(nfa->states);
    IntHashSetIterator it = IntHashSet_iterator(currentStates);
    while(IntHashSetIterator_hasNext(it)) {
        int character = (int) input;
        int state = IntHashSetIterator_next(it);
        possible =  nfa->transition[character][state];
    }
    free(it);
    IntHashSet_free(currentStates);
    return possible;
}

/**
 * Print the given NFA to System.out.
 */
void NFA_print(NFA nfa){
    printf("There are %d states in this NFA\n", nfa->states);
    for(int i = 0; i < nfa->states; i++){
        if(nfa->acceptingStates[i])
            printf("%d is an accepting state\n", i);

    }

    for(int i = 0; i < 128; i++)
    {
        for(int j = 0; j < nfa->states; j++)
        {
            IntHashSetIterator it = IntHashSet_iterator(nfa->transition[i][j]);
            while(IntHashSetIterator_hasNext(it)) {
                int state = IntHashSetIterator_next(it);
                printf("%c transition %d to %d\n", (char)i, j, state);

            }

//            if(dfa->transition[r][c] != -1)
//            {
//                if(c == dfa->states){
//                    printf("%c transitions %d to %d\n", (char) r, c, c);
//
//                }else
//                {
//                    printf("%c transitions %d to %d\n", (char) r, c, c + 1);
//
//                }
//            }
        }
    }
}



