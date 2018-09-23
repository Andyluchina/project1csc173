#include <stdio.h>
#include <string.h>
#include "dfa.h"
#include "nfa.h"


int main(int argc, char* args[]) {
    char* input = "";
    bool result;

    //NFA ending with "car"
    NFA car = new_NFA(4);
    NFA_print(car);
    NFA_set_accepting(car, 3, true);

    NFA_add_transition_all(car, 0, 0);
    NFA_add_transition_all(car, 1, 0);
    NFA_add_transition_all(car, 2, 0);
    NFA_add_transition_all(car, 3, 0);

    NFA_add_transition(car, 0, 'c', 1);
    NFA_add_transition(car, 1, 'a', 2);
    NFA_add_transition(car, 2, 'r', 3);
    printf("Testing NFA that recognizes strings ending in \"car\"\n");
    result = NFA_execute(car, "carcar");
    if(result){
        printf("true \n");
    }
    else{
        printf("false \n");
    }

//    while(strcmp(input, "quit") != 0)
//    {
//        printf("Enter an input to test NFA's ending with car (\"quit\" to quit): ");
//        fgets(input, 100, stdin);
//
//        if(strcmp(input, "quit") == 0)
//        {
//            break;
//        }
//        input[strcspn(input, "\n")] = 0; //removes the new line for when we print out input
//        if(result)
//        {
//            printf("Result for input \"%s\": true\n", input);
//        }else
//        {
//            printf("Result for input \"%s\": false\n", input);
//        }
//
//    }
    NFA_free(car);




    //DFA of exactly xzy
    DFA xzy = new_DFA(4);
    DFA_set_accepting(xzy, 3, 1);
    DFA_set_transition(xzy, 0, 'x', 1);
    DFA_set_transition(xzy, 1, 'z', 2);
    DFA_set_transition(xzy, 2, 'y', 3);
    printf("Testing DFA that recognizes exactly \"xzy\"\n");
    result = DFA_execute(xzy, "test");

    while(strcmp(input, "quit") != 0)
    {
        printf("Enter an input (\"quit\" to quit): ");
        fgets(input, 100, stdin);

        if(strcmp(input, "quit") == 0)
        {
            break;
        }
        result = DFA_execute(xzy, input);
        input[strcspn(input, "\n")] = 0; //removes the new line for when we print out input
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

    printf("\n");
    printf("\n");
    input = "";
    printf("Testing DFA that recognizes any string that starts with the characters \"abc\"\n");
    while(strcmp(input, "quit") != 0)
    {
        printf("Enter an input (\"quit\" to quit): ");
        fgets(input, 100, stdin);

        if(strcmp(input, "quit") == 0)
        {
            break;
        }
        result = DFA_execute(startingWithabc, input);
        input[strcspn(input, "\n")] = 0; //removes the new line for when we print out input
        if(result)
        {
            printf("Result for input \"%s\": true\n", input);
        }else
        {
            printf("Result for input \"%s\": false\n", input);
        }

    }
    DFA_free(startingWithabc);

    //DFA of binary input with an odd number of 0's
    DFA oddZeros = new_DFA(2);
    DFA_set_transition(oddZeros, 0, '0', 1);
    DFA_set_transition(oddZeros, 0, '1', 0);
    DFA_set_transition(oddZeros, 1, '0', 0);
    DFA_set_transition(oddZeros, 1, '1', 1);
    DFA_set_accepting(oddZeros, 1, 1);
    input = "";
    printf("\n");
    printf("\n");
    printf("Testing DFA that recognizes binary input with an odd number of 0's\n");
    while(strcmp(input, "quit") != 0)
    {
        printf("Enter an input (\"quit\" to quit): ");
        fgets(input, 100, stdin);

        if(strcmp(input, "quit") == 0)
        {
            break;
        }
        result = DFA_execute(oddZeros, input);
        input[strcspn(input, "\n")] = 0; //removes the new line for when we print out input
        if(result)
        {
            printf("Result for input \"%s\": true\n", input);
        }else
        {
            printf("Result for input \"%s\": false\n", input);
        }

    }
    DFA_free(oddZeros);

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
    input = "";
    printf("\n");
    printf("\n");
    printf("Testing DFA that recognizes binary input with an odd number of both 0's and 1's\n");
    while(strcmp(input, "quit") != 0)
    {
        printf("Enter an input (\"quit\" to quit): ");
        fgets(input, 100, stdin);

        if(strcmp(input, "quit") == 0)
        {
            break;
        }
        result = DFA_execute(oddZerosAndOnes, input);
        input[strcspn(input, "\n")] = 0; //removes the new line for when we print out input
        if(result)
        {
            printf("Result for input \"%s\": true\n", input);
        }else
        {
            printf("Result for input \"%s\": false\n", input);
        }

    }
    DFA_free(oddZerosAndOnes);

    //DFA containing the string "ing"
    DFA containingING = new_DFA(4);
    DFA_set_accepting(containingING, 3, 1);
    DFA_set_transition_all(containingING, 0, 0);
    DFA_set_transition(containingING, 0, 'i', 1);
    DFA_set_transition(containingING, 1, 'n', 2);
    DFA_set_transition(containingING, 2, 'g', 3);
    DFA_set_transition_all(containingING, 3, 3);
    input = "";
    printf("\n");
    printf("\n");
    printf("Testing DFA that recognizes any string that contains \"ing\"\n");
    while(strcmp(input, "quit") != 0)
    {
        printf("Enter an input (\"quit\" to quit): ");
        fgets(input, 100, stdin);

        if(strcmp(input, "quit") == 0)
        {
            break;
        }
        result = DFA_execute(containingING, input);
        input[strcspn(input, "\n")] = 0; //removes the new line for when we print out input
        if(result)
        {
            printf("Result for input \"%s\": true\n", input);
        }else
        {
            printf("Result for input \"%s\": false\n", input);
        }

    }


}