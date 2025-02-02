#include <stdio.h>

int main() 
{
    int a = 0;
    int b = 0;

    printf("Enter a: ");
    scanf("%d",&a);

    printf("Enter b: ");
    scanf("%d",&b);
    
    int expected_val = a * b;

    int rem = 0;
    int num_size = 16;
    if (b < 0) b += 1 << num_size;

    for (int i = sizeof(int) * 8 / 2; i > 0; i--)
    {   
        if ((b & 1) && !rem) {
            b = b + (-a << num_size);
        } else if (!(b & 1) && rem) {
            b = b + (a << num_size); 
        }
        
        rem = b & 1;
        b = b >> 1;
    }

    printf("Answer by Booth's Algorithm: %d\n", b);
    printf("Actual answer: %d\n", expected_val);

}