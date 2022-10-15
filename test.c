#include <stdio.h>
#include "products.h"
#include "/home/parijat/Codes/mylibs-c/myio/myio.h"
#include "/home/parijat/Codes/mylibs-c/myalgo/myalgo.h"

int main(void)
{
    int c;
    while(1)
    {
        printf("Enter 1 to Exit, 2 for Products: ");
        c = get_int();
        if (c == 2)
            myproducts();
        else if (c == 1)
            break;
        else
            printf("Invalid Input. Try Again\n");
    }
}