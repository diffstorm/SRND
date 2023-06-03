#include "SRND.h"
#include "HAL.h"

#include <stdio.h>
#include <string.h>

static void doTransaction(u8 *UN, u8 *AC)
{
    // use UN in the transaction
    // retrieve AC (if available)
    HAL_TRNG(AC, 8);
}

static int SRND_test()
{
    int pass = 0;
    u8 TID[8] = {1, 2, 3, 4, 'E', 'R', 'A', 'Y'};
    u8 IFDSN[8] = {1, 2, 3, 4, 'E', 'R', 'A', 'Y'};
    u32 TVP;
    u8 RAND[8];
    u8 UN[4];
    u8 AC[8];
    // Get a time-varying parameter
    TVP = HAL_Tick();
    // Generate a weak random number (if available)
    HAL_TRNG(RAND, 8);
    // Get Q and generate P for the current session
    SRND_PowerUp(TID, IFDSN, TVP, RAND);

    for(int i = RAND[0] & 0x0F; i > 0; i--)
    {
        // Generate a weak random number (if available)
        HAL_TRNG(RAND, sizeof(RAND));
        // Get the Terminal Unpredictable Number
        SRND_BeforeTransaction(RAND, UN);
        printf("\tUN : %02X%02X%02X%02X\n", UN[0], UN[1], UN[2], UN[3]);
        //
        // Transaction
        doTransaction(UN, AC);
        //
        // Get a time-varying parameter
        TVP = HAL_Tick();
        // Generate a weak random number (if available)
        HAL_TRNG(RAND, sizeof(RAND));
        // Refresh P - Pre-image of UN (even if transaction fails)
        SRND_AfterTransaction(TVP, RAND, AC);
        pass++;
    }

    // Store P as Q - Persistent variant of P
    SRND_PowerDown();
    return pass;
}

int main()
{
    for(int i = 1; i < 5; i++)
    {
        printf("SRND test %d\n", i);
        int tests = SRND_test();
        printf("SRND test %d has %d transactions\n", i, tests);
    }

    return 0;
}
