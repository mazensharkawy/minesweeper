#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "function.h"

int main()
{

    int i=0;
    printf("1.Start Game\n2.Load Game\n3.Leaderboard\nEnter the no. of the desired operation");
    scanf("%d",&i);
    while(i<1 || i>3)
    {
        printf("Please enter a valid number");
        scanf("%d",&i);
    }
    switch(i)
    {
    case 1:
        start();
    case 2:
        load();
    case 3:
        leaders();
    }
}


