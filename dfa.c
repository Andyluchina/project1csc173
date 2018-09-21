

#include <stdbool.h>
#include <stdio.h>
#include<stdlib.h>
#include <string.h>
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

 //debugged
DFA new_DFA(int nstates){
    struct DFA* newDFA = (struct DFA*)malloc(sizeof(struct DFA));
    newDFA->startState = 0; //was equal to 0
    newDFA->states = nstates;
    newDFA->acceptingStates= (bool*)calloc((size_t)nstates,sizeof(bool)); //I have no clue what (size_t) is but clion said to use it for signed values of type int
    newDFA->transition = (int**)malloc(128*sizeof(int*));
    for(int i=0; i<128; i++){
        newDFA->transition[i] = (int*)malloc(nstates* sizeof(int));
    }
    for(int i = 0; i < 128; i++)
    {
        DFA_set_transition_all(newDFA, i, -1);
    }

    return newDFA;
}



/**
 * Free the given DFA.
 */

//debugged
void DFA_free(DFA dfa) {
    for (int i = 0; i < 128; i++)
    {
        int* currentIntPtr = dfa->transition[i];
        free(currentIntPtr);
    }

    free(dfa->transition);
    dfa->transition = NULL;
    dfa->acceptingStates = NULL;
    free(dfa->acceptingStates);
    dfa->acceptingStates = NULL;
    free(dfa);
    dfa = NULL;
    printf("DFA_free done!");

}

/**
 * Return the number of states in the given DFA.
 */

//debugged
int DFA_get_size(DFA dfa) {
    return dfa->states;
}

/**
 * Return the state specified by the given DFA's transition function from
 * state src on input symbol sym.
 */

//debugged
int DFA_get_transition(DFA dfa, int src, char sym) {
    int ascii = (int)sym;
    return dfa->transition[src][ascii];
}

/**
 * For the given DFA, set the transition from state src on input symbol
 * sym to be the state dst.
 */

//debugged
void DFA_set_transition(DFA dfa, int src, char sym, int dst) {
    int ascii = (int)sym;
    dfa->transition[src][ascii] = dst;
}
/**
 * Set the transitions of the given DFA for each symbol in the given str.
 * This is a nice shortcut when you have multiple labels on an edge between
 * two states.
 */

//debugged
void DFA_set_transition_str(DFA dfa, int src, char *str, int dst) {
    printf("enter DFA_set_transition_str\n");
    for (int t = 0; t < (signed)strlen(str); t++) {
        char c = str[t];
        printf("c: %c, c to int: %d\n", c, (int)c);
        dfa->transition[src][(int)c] = dst;
    }
}

/**
 * Set the transitions of the given DFA for all input symbols.
 * Another shortcut method.
 */
//src is the number of rows
//not sure if debugged
void DFA_set_transition_all(DFA dfa, int src, int dst) {
        for (int j = 0; j < dfa->states; j++) {

            dfa->transition[src][j] = dst;

            //printf("[%d, %d] changed to %d\n", src,j,dst);
        }

}
/**
 * Set whether the given DFA's state is accepting or not.
 */

//debugged
void DFA_set_accepting(DFA dfa, int state, bool value) {
   // printf("fucking accept");
    dfa->acceptingStates[state] = value;
}

/**
 * Return true if the given DFA's state is an accepting state.
 */

//not sure if debugged
bool DFA_get_accepting(DFA dfa, int state) {
    return dfa->acceptingStates[state];
}

/**
 * Run the given DFA on the given input string, and return true if it accepts
 * the input, otherwise false.
 */

//absolutely fucked
bool DFA_execute(DFA dfa, char *input) {
    printf("fuck7\n");
    int state = dfa->startState;
    printf("fuck8\n");
    char *t = input; //this line doesn't work. need to figure out how to read each character in the *input
    printf("t: %s", t);
    for (char *t = input; *t != '\0'; t++) {
        printf("t: %s\n", t);
        if(state == -1)
        {
           return false;
        }
        state = dfa->transition[state][(int)t];
    }
    printf("fuck9\n");
    return DFA_get_accepting(dfa, state);
}

/**
 * Print the given DFA to System.out.
 */

//tbd
void DFA_print(DFA dfa);




