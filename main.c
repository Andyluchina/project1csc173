#include <stdio.h>
#include "dfa.h"
#include "nfa.h"


int main(int argc, char* args[])
{

    NFA car = new_NFA(4);
    NFA_set_accepting(car, 4, true);

    NFA_add_transition_all(car, 0, 0);
    NFA_add_transition_all(car, 1, 0);
    NFA_add_transition_all(car, 2, 0);
    NFA_add_transition_all(car, 3, 0);

    NFA_add_transition(car, 0, 'c', 1);
    NFA_add_transition(car, 1, 'a', 2);
    NFA_add_transition(car, 2, 'r', 3);
    printf("created");
    if(NFA_execute(car, "car")){
        printf("SUCCESS");
    }

    NFA_free(car);



    //DFA of exactly xzy
    DFA xzy = new_DFA(4);
    printf("YO WHAT THE FUCK: %d\n", DFA_get_size(xzy));
    DFA_set_accepting(xzy, 3, 1);
//    size_t size_acceptingStates = sizeof(xzy->acceptingStates)/(xzy->acceptingStates[0]);

    printf("accepted\n");

    DFA_set_transition(xzy, 0, 'x', 1);
    DFA_set_transition(xzy, 1, 'z', 2);
    DFA_set_transition(xzy, 2, 'y', 3);
//    char* str = "xzy";
//    DFA_set_transition_str(xzy, 0, str, 1);
//    printf("DFA_set_transition_str \"working\"\n");


//    printf("is state 3 accepting: %d\n", DFA_get_accepting(xzy,3));
//    printf("is state 1 accepting: %d\n", DFA_get_accepting(xzy,1));
    //  printf("bool: %d\n", DFA_execute(xzy, "abc"));


//    DFA_print(xzy);
//    if(DFA_execute(xzy, "xzy")){
//        printf("xzy is accepted\n");
//    }else{
//        printf("xzy is rejected\n");
//    }
//    // printf("bool: %d\n", DFA_execute(xzy, "xzy"));
//
//    if(DFA_execute(xzy, "abc")){
//        printf("abc is accepted\n");
//    }else{
//        printf("abc is rejected\n");
//    }

    DFA_print(xzy);

    DFA_free(xzy);

    //DFA of any string starting with abc
    DFA startingWithabc = new_DFA(4);
    DFA_set_transition(startingWithabc, 0, 'a', 1);
    DFA_set_transition(startingWithabc, 1, 'b', 2);
    DFA_set_transition(startingWithabc, 2, 'c', 3);
    DFA_set_transition_all(startingWithabc, 3, 3);
    DFA_set_accepting(startingWithabc, 3, 1);
    DFA_print(startingWithabc);
    if(DFA_execute(startingWithabc, "abclkasdjflsadjlfijsadlfjalksdjlkdsajlkasla;ljas;lkj;lkadsfj;lkajf;lkadsjf;lkaj;lkfjsad;lkfja;dslfj")){
        printf("abc is accepted\n");
    }else{
        printf("abc is rejected\n");
    }


    //DFA of binary input with an odd number of 0's
    DFA oddZeros = new_DFA(2);

    DFA_set_transition(oddZeros, 0, '1', 1);
    


//    printf("how does this make any sense");
    //void DFA_set_transition(DFA dfa, int src, char sym, int dst)
    //void DFA_set_transition_all(DFA dfa, int src, int dst)

//    for(int i = 0; i < DFA_get_size(xzy) - 1; i++)
//    {
//        DFA_set_transition_all(xzy, i, -1);
//    }

//    printf("hello\n");
//          DFA_free(xzy);
//    printf("hello hello\n");


//    printf("bool: %d\n", DFA_execute(xzy, "xyzz"));

    /*
    struct DFA abc;
    abc.states = { 0,1,2,3 };
    abc.startState= 2*/
}