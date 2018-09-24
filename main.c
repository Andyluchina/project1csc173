#include <stdio.h>
#include <string.h>
#include "dfa.h"
#include "nfa.h"
#include "NFAtoDFA.h"

DFA createXZY()
{
    DFA xzy = new_DFA(4);
    DFA_set_accepting(xzy, 3, 1);
    DFA_set_transition(xzy, 0, 'x', 1);
    DFA_set_transition(xzy, 1, 'z', 2);
    DFA_set_transition(xzy, 2, 'y', 3);
    return xzy;
}

DFA createABC()
{
    DFA startingWithabc = new_DFA(4);
    DFA_set_transition(startingWithabc, 0, 'a', 1);
    DFA_set_transition(startingWithabc, 1, 'b', 2);
    DFA_set_transition(startingWithabc, 2, 'c', 3);
    DFA_set_transition_all(startingWithabc, 3, 3);
    DFA_set_accepting(startingWithabc, 3, 1);
    return startingWithabc;
}

DFA createOddZeros()
{
    DFA oddZeros = new_DFA(2);
    DFA_set_transition(oddZeros, 0, '0', 1);
    DFA_set_transition(oddZeros, 0, '1', 0);
    DFA_set_transition(oddZeros, 1, '0', 0);
    DFA_set_transition(oddZeros, 1, '1', 1);
    DFA_set_accepting(oddZeros, 1, 1);
    return oddZeros;
}

DFA createOddZerosAndOnes()
{
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
    return oddZerosAndOnes;
}

DFA createING()
{
    DFA containingING = new_DFA(4);
    DFA_set_accepting(containingING, 3, 1);
    DFA_set_transition_all(containingING, 0, 0);
    DFA_set_transition(containingING, 0, 'i', 1);
    DFA_set_transition(containingING, 1, 'n', 2);
    DFA_set_transition(containingING, 2, 'g', 3);
    DFA_set_transition_all(containingING, 3, 3);
    return containingING;
}

NFA createEndingcar()
{
    NFA car = new_NFA(4);
    NFA_set_accepting(car, 3, true);
    NFA_add_transition(car, 0, 'c', 1);
    NFA_add_transition(car, 1, 'a', 2);
    NFA_add_transition(car, 2, 'r', 3);

    NFA_add_transition_all(car, 0, 0);
    NFA_add_transition_all(car, 1, 0);
    NFA_add_transition_all(car, 2, 0);
    NFA_add_transition_all(car, 3, 0);
    return car;
}

NFA createContainingcar()
{
    NFA containCar = new_NFA(4);
    NFA_set_accepting(containCar, 3, true);
    NFA_add_transition_all(containCar, 0, 0);
    NFA_add_transition_all(containCar, 1, 0);
    NFA_add_transition_all(containCar, 2, 0);
    NFA_add_transition_all(containCar, 3, 3);
    NFA_add_transition(containCar, 0, 'c', 1);
    NFA_add_transition(containCar, 1, 'a', 2);
    NFA_add_transition(containCar, 2, 'r', 3);
    return containCar;
}

NFA createWashington()
{
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
    return washington;
}

NFA createIPattern(){
    NFA ipattern = new_NFA(5);
    NFA_set_accepting(ipattern, 4, true);
    NFA_add_transition_all(ipattern, 0, 0);
    NFA_add_transition_all(ipattern, 1, 0);
    NFA_add_transition_all(ipattern, 2, 0);
    NFA_add_transition_all(ipattern, 3, 0);
    NFA_add_transition_all(ipattern, 4, 4);

    NFA_add_transition(ipattern, 0, 'i', 1);
    NFA_add_transition(ipattern, 1, 'p', 2);
    NFA_add_transition(ipattern, 2, 'a', 3);
    NFA_add_transition(ipattern, 3, 't', 4);
    return ipattern;
}
//testing   NFA that is a interesting pattern pattern that contains ipat


void dfaREPL(DFA dfa) {
    bool result;
    char input[256] = "";


    while (strcmp(input, "quit") != 0) {
        printf("Enter an input (\"quit\" to quit): ");
        fgets(input, sizeof(input), stdin);
        if (strcmp(input, "quit") == 0) {
            break;
        }
        result = DFA_execute(dfa, input);
        input[strcspn(input, "\n")] = 0; //removes the new line for when we print out input
        if (result) {
            printf("Result for input \"%s\": true\n", input);
        } else {
            printf("Result for input \"%s\": false\n", input);
        }


    }
    DFA_free(dfa);
    printf("\n");

    //DFA of exactly xzy
}

void nfaREPL(NFA nfa)
{
    char input[256] = "";
    bool result;

    while(strcmp(input, "quit") != 0)
    {
        printf("Enter an input (\"quit\" to quit): ");
        fgets(input, 100, stdin);
        if(strcmp(input, "quit") == 0)
        {
            break;
        }
        result = NFA_execute(nfa, input);
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
}

int main(int argc, char* args[]) {
    // 1a
    printf("Testing DFA that recognizes exactly the string \"xzy\"\n");
    DFA xzy = createXZY();
    dfaREPL(xzy);
    //1b
    printf("Testing DFA that recognizes any string that starts with the characters \"abc\"\n");
    DFA startingWithabc = createABC();
    dfaREPL(startingWithabc);
    //1c
    printf("Testing DFA that recognizes binary input with an odd number of 0's\n");
    DFA oddZeros = createOddZeros();
    dfaREPL(oddZeros);
    //1d
    printf("Testing DFA that recognizes binary input with an odd number of both 0's and 1's\n");
    DFA oddZerosAndOnes = createOddZerosAndOnes();
    dfaREPL(oddZerosAndOnes);
    //1e
    printf("Testing DFA that recognizes any string that contains \"ing\"\n");
    DFA containingING = createING();
    dfaREPL(containingING);
    //2a
    printf("Testing NFA that recognizes strings ending in \"car\"\n");
    NFA car = createEndingcar();
    nfaREPL(car);
    //2b
    printf("Testing NFA that recognizes strings containing \"car\"\n");
    NFA containCar = createContainingcar();
    nfaREPL(containCar);
    //2c
    printf("Testing NFA that is not a partial anagram of washington\n");
    NFA washington = createWashington();
    nfaREPL(washington);
    //2d
    printf("Testing NFA that contains the string \"ipat\"\n");
    NFA ipat = createIPattern();
    nfaREPL(ipat);

    //3
    printf("Testing DFA from NFA that recognizes strings ending in \"car\"\n");
    DFA carDFA = NFAtoDFA(car);
    printf("Number of states in the dfa: %d \n", DFA_get_size(carDFA));
    dfaREPL(carDFA);

    printf("Testing DFA from NFA that recognizes strings containing \"car\"\n");
    DFA containCarDFA = NFAtoDFA(containCar);
    printf("Number of states in the dfa: %d \n", DFA_get_size(containCarDFA));
    dfaREPL(containCarDFA);

    printf("Testing NFA from DFA that is not a partial anagram of washington\n");
    DFA washingtonDFA = NFAtoDFA(washington);
    printf("Number of states in the dfa: %d \n", DFA_get_size(washingtonDFA));
    dfaREPL(washingtonDFA);



    NFA_free(washington);
    NFA_free(containCar);
    NFA_free(car);
    NFA_free(ipat);

}