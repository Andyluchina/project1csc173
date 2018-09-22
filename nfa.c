
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
NFA new_NFA(int nstates){
    struct NFA* newNFA = (struct NFA*)malloc(sizeof(struct NFA));
    newNFA->startState = 0; //was equal to 0
    newNFA->states = nstates;
    newNFA->acceptingStates= (bool*)calloc((size_t)nstates,sizeof(bool)); //I have no clue what (size_t) is but clion said to use it for signed values of type int
    newNFA->transition = (int**)malloc(128*sizeof(int*));
    for(int i=0; i<128; i++){
        newNFA->transition[i] = (int*)malloc(nstates * sizeof(int));
    }

/**
 * Free the given NFA.
 */
void NFA_free(NFA nfa){

}

/**
 * Return the number of states in the given NFA.
 */
int NFA_get_size(NFA nfa){

}

/**
 * Return the set of next states specified by the given NFA's transition
 * function from the given state on input symbol sym.
 */
extern Set NFA_get_transitions(NFA nfa, int state, char sym);

/**
 * For the given NFA, add the state dst to the set of next states from
 * state src on input symbol sym.
 */
extern void NFA_add_transition(NFA nfa, int src, char sym, int dst);

/**
 * Add a transition for the given NFA for each symbol in the given str.
 */
extern void NFA_add_transition_str(NFA nfa, int src, char *str, int dst);

/**
 * Add a transition for the given NFA for each input symbol.
 */
extern void NFA_add_transition_all(NFA nfa, int src, int dst);

/**
 * Set whether the given NFA's state is accepting or not.
 */
extern void NFA_set_accepting(NFA nfa, int state, bool value);

/**
 * Return true if the given NFA's state is an accepting state.
 */
extern bool NFA_get_accepting(NFA nfa, int state);

/**
 * Run the given NFA on the given input string, and return true if it accepts
 * the input, otherwise false.
 */
extern bool NFA_execute(NFA nfa, char *input);

/**
 * Print the given NFA to System.out.
 */
extern void NFA_print(NFA nfa);

#endif
