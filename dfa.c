

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
DFA new_DFA(int nstates) {
    struct DFA* newDFA = (struct DFA*)malloc(sizeof(struct DFA));
    newDFA->startState = 0; //was equal to 0
    newDFA->states = nstates;
    newDFA->acceptingStates= (bool*)calloc((size_t)nstates,sizeof(bool)); //I have no clue what (size_t) is but clion said to use it for signed values of type int
    newDFA->transition = (int**)malloc(128*sizeof(int*));
    for(int i=0; i<128; i++){
        newDFA->transition[i] = (int*)malloc(nstates * sizeof(int));
    }
    for(int i = 0; i < 128; i++)
    {
        for(int j = 0; j < nstates; j++){
            newDFA->transition[i][j]=-1;
        }
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
        free(dfa->transition[i]);
    }
    free(dfa->transition);
    dfa->transition = NULL;
    dfa->acceptingStates = NULL;
    free(dfa->acceptingStates);
    dfa->acceptingStates = NULL;
    free(dfa);
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
    return dfa->transition[ascii][src];
}

/**
 * For the given DFA, set the transition from state src on input symbol
 * sym to be the state dst.
 */

//debugged
void DFA_set_transition(DFA dfa, int src, char sym, int dst) {
    int ascii = (int)sym;
//    printf("before transfer: %d",dfa->transition[ascii][src]);
    dfa->transition[ascii][src] = dst;
//    printf("after transfer: %d",dfa->transition[ascii][src]);
}
/**
 * Set the transitions of the given DFA for each symbol in the given str.
 * This is a nice shortcut when you have multiple labels on an edge between
 * two states.
 */

//debugged
void DFA_set_transition_str(DFA dfa, int src, char *str, int dst) {
//    printf("enter DFA_set_transition_str\n");
    for (int t = 0; t < (signed)strlen(str); t++) {
        char c = str[t];
//        printf("c: %c, c to int: %d\n", c, (int)c);
        dfa->transition[src][(int)c] = dst;
    }
}

/**
 * Set the transitions of the given DFA for all input symbols.
 * Another shortcut method.
 */
//src is the number of rows
//debugged
void DFA_set_transition_all(DFA dfa, int src, int dst) {
        for (int j = 0; j < 128; j++) {

            dfa->transition[j][src] = dst;


        }

}
/**
 * Set whether the given DFA's state is accepting or not.
 */

//debugged
void DFA_set_accepting(DFA dfa, int state, bool value) {
    dfa->acceptingStates[state] = value;
//    printf("as: %d", dfa->acceptingStates[state]);
}

/**
 * Return true if the given DFA's state is an accepting state.
 */

//debugged
bool DFA_get_accepting(DFA dfa, int state) {
    if(state == -1){
        return false;
    }
    return dfa->acceptingStates[state];
}

/**
 * Run the given DFA on the given input string, and return true if it accepts
 * the input, otherwise false.
 */

bool DFA_execute(DFA dfa, char *input) {
    int state = dfa->startState;
    for (int t = 0; t < (signed) strlen(input)-1; t++) {
        if(state == -1)
        {
            return false;
        }
        state = dfa->transition[(int)input[t]][state];
    }
    return DFA_get_accepting(dfa, state);
}

/**
 * Print the given DFA to System.out.
 */

//prints the number of states and the transitions
void DFA_print(DFA dfa)
{
    printf("There are %d states in this DFA\n", dfa->states);
    for(int i = 0; i < dfa->states; i++){
        if(DFA_get_accepting(dfa, i))
        {
            printf("%d is an accepting state\n", i);
        }
    }
    for(int r = 0; r < 128; r++)
    {
        for(int c = 0; c < dfa->states; c++)
        {
            if(dfa->transition[r][c] != -1)
            {
                printf("%c transitions %d to %d\n", (char) r, c, dfa->transition[r][c]);
            }
        }
    }
}




