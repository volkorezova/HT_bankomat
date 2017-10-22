//
//  main.c
//  Bankomat
//
//  Created by Tatyana Volkorezova on 19.10.2017.
//  Copyright © 2017 shpp.com. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int BASIC_BAL=100000;
const int cellsNum=5000;
const int generalAttempt=2;

int main() {
    int pinArray[cellsNum];
    int balArray[cellsNum];
    int randPin = 0;
    int indexForBalance=0;
    int sum=0, i=0, j=0;
    int adminSelect, userSelect;
    int adminPin=1111;
    int ok, enterPin;
    int countDigits=0, countAttempt=0;
    
    srand(time(NULL));
    
    //fill array with random pin
    for (int i = 0; i < cellsNum; i++){
        randPin = rand() % cellsNum;
        pinArray[i] = 1000 + randPin;
       // printf("%d: ", pinArray[i]);
    }
    
    //fill array with random balance
    for ( int i = 0; i < cellsNum; i ++){
        balArray[i]  = BASIC_BAL + i;
        // printf("%d ", balArray[i]);
    }
    
    // user can enter only three times valid PIN
    for (int countAttempt = 0; countAttempt <= 2; countAttempt++){
        for(;;){
            printf("Enter PIN kod: ");
            ok=scanf("%d", &enterPin);
            fpurge(stdin);
            
            if (enterPin==adminPin)
                goto againAdmin;
            
            for (i = 0; i < cellsNum; i++){
                if(enterPin == pinArray[i]){
                    indexForBalance = i;
                    goto againUser;
                }
            }
                    
            
            if (!ok){
                printf("It's a string. Try again\n");
                fpurge(stdin);
                continue;
            } else if (enterPin < 0){
                printf("Negative number. Pls enter correct pin with 4 digits\n");
                fpurge(stdin);
                continue;
            }
            //calculation of entered digits for pin
            countDigits = 1 + (int)log10(enterPin);
            if ((countDigits < 4) || (countDigits > 4)){
                printf("Entered PIN has incorrect length. PIN should be 4 digits\n");
                continue;
            }
            break;
        }
        //check on 3 attepts
        if (countAttempt==generalAttempt){
            printf("\n-------->BYE! Unfortunately, your card was rejected<--------\n");
            break;
        }
    }
    
    
    //check for roles
    //ADMIN role
    if (enterPin == adminPin){
    againAdmin:printf("\nYou are ADMIN!\n");
        printf("Options that you have:\n");
        printf("1: View balance of all cards \n");
        printf("2: Clear all card balance \n");
        printf("3: Exit\nPls make a choice: ");
        scanf("%d", &adminSelect);
        fpurge(stdin);
        switch (adminSelect) {
                // option of view of all cells, PINs, balances
            case 1:
                printf("View all information about cells\n");
                for (i = 0, j = 0; i < cellsNum; i++, j++){
                    printf("Cell number:%d, PIN: %d, Balance:%d \n", i+1, pinArray[i], balArray[j]);
                }
                break;
                // clear balance for all cards
            case 2:
                printf("Balances for all cards were cleared:\n");
                memset (balArray, 0, sizeof(balArray));
                for (i = 0, j = 0; i < cellsNum; i++, j++){
                    printf("Cell number:%d, PIN: %d, Balance:%d \n", i+1, pinArray[i], balArray[j]);
                }
                break;
            case 3:
                return 0;
                //case when user enter incorrect value
            default:
                printf("\nERROR - Incorrect choice. Pls select the next: \n");
                goto againAdmin;
                
        }
    } else{
        //USER role
        for (i = 0; i < cellsNum; i++){
            if(enterPin == pinArray[i]){
                indexForBalance = i;
            againUser:printf("\nYou are USER! \n");
                printf("Options that you have:\n");
                printf("1: View balance of YOUR card \n");
                printf("2: Add money to card balance \n");
                printf("3: Take money from your card \n");
                printf("4: Exit\nPls make a choice: ");
                scanf("%d", &userSelect);
                fpurge(stdin);
                switch (userSelect) {
                        
                        // option of view of selected cell, PIN, balance
                    case 1:
                        printf("View balance of YOUR card: \n");
                        printf("---- Cell number:%d, PIN: %d, Balance:%d ---- \n", i+1, pinArray[indexForBalance], balArray[indexForBalance]);
                        break;
                        
                        // add money to card balance
                    case 2:
                        printf("Pls enter sum for adding to your balance: ");
                        scanf("%d", &sum);
                        fpurge(stdin);
                        printf("---- Cell number:%d, PIN: %d, Initial balance: %d, New balance:%d(added %d) ---- \n", i+1, pinArray[indexForBalance], balArray[indexForBalance], balArray[indexForBalance]+sum, sum);
                        break;
                        
                        // take money from card
                    case 3:
                        printf("Pls enter sum for taking from your balance: ");
                        scanf("%d", &sum);
                        fpurge(stdin);
                        if (sum > balArray[indexForBalance]){
                            printf("!!!!!You can't take money more than you have!!!!!\n");
                            continue;
                        }
                        printf("---- Cell number:%d, PIN: %d, Initial balance: %d, New balance:%d(took %d) ---- \n", i+1, pinArray[i], balArray[j], balArray[j]-sum, sum);
                        break;
                        
                        // exit from bankomat
                    case 4:
                        break;
                    default:
                        printf("\nERROR - Pls make the right choice\n");
                        goto againUser;
                }
                break;
            }
        }
        return 0;
    }
}


