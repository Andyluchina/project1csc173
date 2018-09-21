

#include <stdbool.h>
#include <stdio.h>
#include<stdlib.h>
#include "dfa.h"
#include "LinkedList.h"


/**
 * Allocate and return a new DFA containing the given number of states.
 */
 struct DFA {
         int startState;
         int** transition;
         bool* acceptingStates;
         int states;
 };
DFA new_DFA(int nstates){
    struct DFA* newDFA = (struct DFA*)malloc(sizeof(struct DFA));
    newDFA->startState = 0; //was equal to 0
    newDFA->states = nstates;
    newDFA->acceptingStates= (bool*)calloc(nstates,sizeof(bool));
    newDFA->transition = (int**)malloc(128*sizeof(int*));
    for(int i=0; i<128; i++){
        newDFA->transition[i] = (int*)malloc(nstates* sizeof(int));
    }

    return newDFA;
}



/**
 * Free the given DFA.
 */
void DFA_free(DFA dfa) {
    free(dfa->transition);
    dfa->transition = NULL;
    free(dfa->acceptingStates);
    dfa->acceptingStates = NULL;
    free(dfa);
    dfa = NULL;
}

/**
 * Return the number of states in the given DFA.
 */
int DFA_get_size(DFA dfa) {
    return dfa->states;
}

/**
 * Return the state specified by the given DFA's transition function from
 * state src on input symbol sym.
 */
int DFA_get_transition(DFA dfa, int src, char sym) {
    int ascii = (int)sym;
    return dfa->transition[src][ascii];
}

/**
 * For the given DFA, set the transition from state src on input symbol
 * sym to be the state dst.
 */
void DFA_set_transition(DFA dfa, int src, char sym, int dst) {
    int ascii = (int)sym;
    dfa->transition[src][ascii] = dst;
}
/**
 * Set the transitions of the given DFA for each symbol in the given str.
 * This is a nice shortcut when you have multiple labels on an edge between
 * two states.
 */
void DFA_set_transition_str(DFA dfa, int src, char *str, int dst) {
    for (char*t = str; *t != '\0'; t++) {
        dfa->transition[src][(int)t] = dst;
    }
}

/**
 * Set the transitions of the given DFA for all input symbols.
 * Another shortcut method.
 */
void DFA_set_transition_all(DFA dfa, int src, int dst) {
        for (int j = 0; j < 256; j++) {
            dfa->transition[src][j] = dst;
        }

}
/**
 * Set whether the given DFA's state is accepting or not.
 */
void DFA_set_accepting(DFA dfa, int state, bool value) {
   // printf("fucking accept");
    dfa->acceptingStates[state] = value;
}

/**
 * Return true if the given DFA's state is an accepting state.
 */
bool DFA_get_accepting(DFA dfa, int state) {
    return dfa->acceptingStates[state];
}

/**
 * Run the given DFA on the given input string, and return true if it accepts
 * the input, otherwise false.
 */
bool DFA_execute(DFA dfa, char *input) {
    int state = dfa->startState;
    for (char *t = input; *t != '\0'; t++) {
        if(state == -1)
        {
           return false;
        }
        state = dfa->transition[state][(int)t];
    }
    return DFA_get_accepting(dfa, state);
}

/**
 * Print the given DFA to System.out.
 */
void DFA_print(DFA dfa);




