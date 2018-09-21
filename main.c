#include <stdio.h>
#include "dfa.h"
#include "nfa.h"



//int startState;
//int transition[30][256];
//bool acceptingStates[20];
//int states[30];



int main(int argc, char* args[])
{

    DFA xzy = new_DFA(4);
    printf("YO WHAT THE FUCK: %d.\n", DFA_get_size(xzy));
    DFA_set_accepting(xzy, 4, 1);
    printf("accepted");


    //void DFA_set_transition(DFA dfa, int src, char sym, int dst)
    //void DFA_set_transition_all(DFA dfa, int src, int dst)

    for(int i = 0; i < DFA_get_size(xzy) - 1; i++)
    {
        DFA_set_transition_all(xzy, i, -1);
    }

    printf("hello");
    DFA_free(xzy);

    /*
    struct DFA abc;
    abc.states = { 0,1,2,3 };
    abc.startState= 2*/
}