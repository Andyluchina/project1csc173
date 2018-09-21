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
    set_accepting(xzy, 4);

    printf("hello");


    /*
    struct DFA abc;
    abc.states = { 0,1,2,3 };
    abc.startState= 2*/
}