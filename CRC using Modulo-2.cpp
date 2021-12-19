#include <stdio.h>
#include <conio.h>

int d[7], div[4], r[7];
void dn(int dd[]);

int main()

{

    int i, f = 0;
    long int a;
    printf("-----SENDER'S SIDE-----\n\n");
    printf("Enter code : ");
    scanf("%ld", &a);

    for (i = 3; i > -1; i--)

    {
        d[i] = (long)a % 10;
        a = a / 10;
    }

    d[4] = d[5] = d[6] = 0;
    printf("Enter divisor: ");
    scanf("%ld", &a);
    for (i = 3; i > -1; i--)
    {
        div[i] = a % 10;
        a = a / 10;
    }
    printf("\nData before processing: ");
    for (i = 0; i < 7; i++)
        printf("%d", d[i]);

    dn(d);
    printf("\nGenerated Remainder: %d%d%d\n\n", d[4], d[5], d[6]);

    printf("-----RECEIVER'S SIDE-----\n\n");

    printf("Enter data at Receiver: ");
    scanf("%ld", &a);

    for (i = 6; i > -1; i--)
    {
        r[i] = a % 10;
        a = a / 10;
    }
    dn(r);

    for (i = 4; i < 7; i++)
        if (r[i] == 1)
        {
            f = 1;
            break;
        }
    printf("Receiver's Remainder: ");

    for (i = 4; i < 7; i++)
        printf("%d", r[i]);

    if (f == 1)
        printf("\n\n               Error in Transmission!!\n");
    else
        printf("\n\n               No Error in Transmission!!\n");
    return 0;
}

void dn(int dd[])
{
    int i, j;
    for (i = 0; i < 4; i++)
    {
        if (dd[i] == 0)
            continue;
        for (j = i + 3; j >= i; j--)
        {
            dd[j] = dd[j] ^ div[j - i];
        }
    }
}