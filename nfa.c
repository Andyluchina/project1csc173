
#include <stdbool.h>
#include "LinkedList.h"
#include "nfa.h"
#include "BitSet.c"

struct NFA{
    int startState;
    BitSet** transition;
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
    newNFA->transition = (struct BitSet **) malloc(128 * sizeof(BitSet *));
    for (int i = 0; i < 128; i++) {
        newNFA->transition[i] = (BitSet *) malloc(nstates * sizeof(BitSet));
    }
}
/**
 * Free the given NFA.
 */
void NFA_free(NFA nfa){

    for(int i=0; i<128; i++){
        free(nfa->transition[i]);
    }
    free(nfa->transition);
    free(nfa->acceptingStates);
    free(nfa);
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
Set NFA_get_transitions(NFA nfa, int state, char sym){
    return nfa->transition[(int)sym][state];
};

/**
 * For the given NFA, add the state dst to the set of next states from
 * state src on input symbol sym.
 */
void NFA_add_transition(NFA nfa, int src, char sym, int dst){
    BitSet_insert(nfa->transition[(int)sym][src],dst);
};

/**
 * Add a transition for the given NFA for each symbol in the given str.
 */
void NFA_add_transition_str(NFA nfa, int src, char *str, int dst){
    for(int i=0; i<strlen(str); i++){
        NFA_add_transition(nfa, src, str[i], dst);
    }
};

/**
 * Add a transition for the given NFA for each input symbol.
 */
void NFA_add_transition_all(NFA nfa, int src, int dst){
    for(int i=0; i<128; i++){
        BitSet_insert(nfa->transition[i][src],dst);
    }
};

/**
 * Set whether the given NFA's state is accepting or not.
 */
void NFA_set_accepting(NFA nfa, int state, bool value){
    nfa->acceptingStates[state]=value;
};

/**
 * Return true if the given NFA's state is an accepting state.
 */
bool NFA_get_accepting(NFA nfa, int state){
    return nfa->acceptingStates[state];
};

/**
 * Run the given NFA on the given input string, and return true if it accepts
 * the input, otherwise false.
 */
bool NFA_execute(NFA nfa, char *input){
    for(int i=0; i<strlen(input); i++){

    }
};


//Set get_all_possible_states(NFA nfa, )

/**
 * Print the given NFA to System.out.
 */
void NFA_print(NFA nfa);
