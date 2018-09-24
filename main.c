#include <stdio.h>
#include <string.h>
#include "dfa.h"
#include "nfa.h"


int main(int argc, char* args[]) {
    char* input = "";
    bool result;

//    NFA ending with "car"
    NFA car = new_NFA(4);
    NFA_set_accepting(car, 3, true);
    NFA_add_transition(car, 0, 'c', 1);
    NFA_add_transition(car, 1, 'a', 2);
    NFA_add_transition(car, 2, 'r', 3);

    NFA_add_transition_all(car, 0, 0);
    NFA_add_transition_all(car, 1, 0);
    NFA_add_transition_all(car, 2, 0);
    NFA_add_transition_all(car, 3, 0);
    printf("Testing NFA that recognizes strings ending in \"car\"\n");
    while(strcmp(input, "quit") != 0)
    {
        printf("Enter an input (\"quit\" to quit): ");
        fgets(input, 100, stdin);

        if(strcmp(input, "quit") == 0)
        {
            break;
        }
        input[strcspn(input, "\n")] = 0; //removes the new line for when we print out input
        result = NFA_execute(car, input);
        if(result)
        {
            printf("Result for input \"%s\": true\n", input);
        }else
        {
            printf("Result for input \"%s\": false\n", input);
        }

    }
    printf("\n");
    printf("\n");
    NFA_free(car);


//NFA containing car
    NFA containCar = new_NFA(4);
    NFA_set_accepting(containCar, 3, true);
    NFA_add_transition_all(containCar, 0, 0);
    NFA_add_transition_all(containCar, 1, 0);
    NFA_add_transition_all(containCar, 2, 0);
    NFA_add_transition_all(containCar, 3, 3);
    NFA_add_transition(containCar, 0, 'c', 1);
    NFA_add_transition(containCar, 1, 'a', 2);
    NFA_add_transition(containCar, 2, 'r', 3);

    printf("Testing NFA that recognizes strings containing \"car\"\n");
    input = "";
    while(strcmp(input, "quit") != 0)
    {
        printf("Enter an input (\"quit\" to quit): ");
        fgets(input, 100, stdin);

        if(strcmp(input, "quit") == 0)
        {
            break;
        }
        result = NFA_execute(containCar, input);
        input[strcspn(input, "\n")] = 0; //removes the new line for when we print out input
        if(result)
        {
            printf("Result for input \"%s\": true\n", input);
        }else
        {
            printf("Result for input \"%s\": false\n", input);
        }

    }
    printf("\n");
    printf("\n");
    NFA_free(containCar);

    //testing NFA that is an anagram of washington
    NFA washington = new_NFA(20);
    NFA_set_accepting(washington, 2, true);
    NFA_set_accepting(washington, 4, true);
    NFA_set_accepting(washington, 6, true);
    NFA_set_accepting(washington, 8, true);
    NFA_set_accepting(washington, 11, true);
    NFA_set_accepting(washington, 13, true);
    NFA_set_accepting(washington, 15, true);
    NFA_set_accepting(washington, 17, true);
    NFA_set_accepting(washington, 19, true);

    NFA_add_transition_all(washington, 0, 0);

    NFA_add_transition(washington, 0, 'a', 1);
    NFA_add_transition(washington, 0, 'g', 3);
    NFA_add_transition(washington, 0, 'h', 5);
    NFA_add_transition(washington, 0, 'i', 7);
    NFA_add_transition(washington, 0, 'n', 9);
    NFA_add_transition(washington, 0, 'n', 12);
    NFA_add_transition(washington, 0, 'o', 14);
    NFA_add_transition(washington, 0, 's', 16);
    NFA_add_transition(washington, 0, 't', 18);

    NFA_add_transition(washington, 1, 'a', 2);
    NFA_add_transition(washington, 3, 'g', 4);
    NFA_add_transition(washington, 5, 'h', 6);
    NFA_add_transition(washington, 7, 'i', 8);
    NFA_add_transition(washington, 9, 'n', 10);
    NFA_add_transition(washington, 10, 'n', 11);
    NFA_add_transition(washington, 12, 'o', 13);
    NFA_add_transition(washington, 14, 's', 15);
    NFA_add_transition(washington, 16, 't', 17);
    NFA_add_transition(washington, 18, 'w', 19);

    int arr[] = {1, 3, 5, 7, 9, 10, 12, 14, 16, 18};
    int length = 10;
    char arrchar[] = {'a', 'g', 'h', 'i', 'n', 'n', 'o', 's', 't', 'w'};

    for(int i=0; i< length; i++){
        for(int j=0; j<128; j++){
            if((int)arrchar[i]!=j){
                NFA_add_transition(washington, arr[i], (char)j, arr[i]);
            }
        }
    }

    input = "";
    printf("Testing NFA that is not a partial anagram of washington\n");
    while(strcmp(input, "quit") != 0)
    {
        printf("Enter an input (\"quit\" to quit): ");
        fgets(input, 100, stdin);

        if(strcmp(input, "quit") == 0)
        {
            break;
        }
        result = NFA_execute(washington, input);
        input[strcspn(input, "\n")] = 0; //removes the new line for when we print out input
        if(result)
        {
            printf("Result for input \"%s\": true\n", input);
        }else
        {
            printf("Result for input \"%s\": false\n", input);
        }

    }

    NFA_free(washington);





    //testing NFA that is a interesting pattern pattern that contains ing




    //DFA of exactly xzy
    DFA xzy = new_DFA(4);
    DFA_set_accepting(xzy, 3, 1);
    DFA_set_transition(xzy, 0, 'x', 1);
    DFA_set_transition(xzy, 1, 'z', 2);
    DFA_set_transition(xzy, 2, 'y', 3);
    printf("Testing DFA that recognizes exactly \"xzy\"\n");

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
    printf("\n");
    printf("\n");

    //DFA of any string starting with abc
    DFA startingWithabc = new_DFA(4);
    DFA_set_transition(startingWithabc, 0, 'a', 1);
    DFA_set_transition(startingWithabc, 1, 'b', 2);
    DFA_set_transition(startingWithabc, 2, 'c', 3);
    DFA_set_transition_all(startingWithabc, 3, 3);
    DFA_set_accepting(startingWithabc, 3, 1);

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
    printf("\n");
    printf("\n");

    //DFA of binary input with an odd number of 0's
    DFA oddZeros = new_DFA(2);
    DFA_set_transition(oddZeros, 0, '0', 1);
    DFA_set_transition(oddZeros, 0, '1', 0);
    DFA_set_transition(oddZeros, 1, '0', 0);
    DFA_set_transition(oddZeros, 1, '1', 1);
    DFA_set_accepting(oddZeros, 1, 1);
    input = "";
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
    printf("\n");
    printf("\n");
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
    DFA_free(containingING);



}