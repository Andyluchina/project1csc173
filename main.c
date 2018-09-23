#include <stdio.h>
#include <string.h>
#include "dfa.h"
#include "nfa.h"


int main(int argc, char* args[]) {
    char* input = "";
    bool result;

    //DFA of exactly xzy
    DFA xzy = new_DFA(4);
    DFA_set_accepting(xzy, 3, 1);
    DFA_set_transition(xzy, 0, 'x', 1);
    DFA_set_transition(xzy, 1, 'z', 2);
    DFA_set_transition(xzy, 2, 'y', 3);
    printf("Testing DFA that recognizes exactly \"xzy\"\n");
    while(input != "quit")
    {
        printf("Enter an input (\"quit\" to quit): ");
        fgets(input, 100, stdin);
//        input[strcspn(input, "\n")] = 0;
        result = DFA_execute(xzy, input);

        if(result)
        {
            printf("Result for input \"%s\": true\n", input);
        }else
        {
            printf("Result for input \"%s\": false\n", input);
        }

    }

    DFA_free(xzy);

    //DFA of any string starting with abc
    DFA startingWithabc = new_DFA(4);
    DFA_set_transition(startingWithabc, 0, 'a', 1);
    DFA_set_transition(startingWithabc, 1, 'b', 2);
    DFA_set_transition(startingWithabc, 2, 'c', 3);
    DFA_set_transition_all(startingWithabc, 3, 3);
    DFA_set_accepting(startingWithabc, 3, 1);
    DFA_print(startingWithabc);


    //DFA of binary input with an odd number of 0's
    DFA oddZeros = new_DFA(2);
    DFA_set_transition(oddZeros, 0, '0', 1);
    DFA_set_transition(oddZeros, 0, '1', 0);
    DFA_set_transition(oddZeros, 1, '0', 0);
    DFA_set_transition(oddZeros, 1, '1', 1);
    DFA_set_accepting(oddZeros, 1, 1);
    DFA_print(oddZeros);


    //DFA of binary input with an odd number of 0's and 1's
    DFA oddZerosAndOnes = new_DFA(5);
    DFA_set_transition(oddZerosAndOnes, 0, '1', 1);
    DFA_set_transition(oddZerosAndOnes, 1, '1', 0);
    DFA_set_transition(oddZerosAndOnes, 1, '0', 3);
    DFA_set_transition(oddZerosAndOnes, 3, '0', 1);
    DFA_set_transition(oddZerosAndOnes, 0, '0', 2);
    DFA_set_transition(oddZerosAndOnes, 2, '0', 0);
    DFA_set_transition(oddZerosAndOnes, 2, '1', 4);
    DFA_set_transition(oddZerosAndOnes, 4, '1', 2);
    DFA_set_transition(oddZerosAndOnes, 4, '0', 1);
    DFA_set_transition(oddZerosAndOnes, 3, '1', 2);
    DFA_set_accepting(oddZerosAndOnes, 3, 1);
    DFA_set_accepting(oddZerosAndOnes, 4, 1);
    DFA_print(oddZerosAndOnes);


    //DFA containing the string "ing"
    DFA containingING = new_DFA(4);
    DFA_set_accepting(containingING, 3, 1);
    DFA_set_transition_all(containingING, 0, 0);
    DFA_set_transition(containingING, 0, 'i', 1);
    DFA_set_transition(containingING, 1, 'n', 2);
    DFA_set_transition(containingING, 2, 'g', 3);
    DFA_set_transition_all(containingING, 3, 3);
    DFA_print(containingING);


}