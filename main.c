#include <stdio.h>

int booth(int a, int b)
{   
    // Logic:
    // All operations are done in b itself
    // Here both A & Q register vals are stored in b
    // Q-1 is stored in rem
    // The function returns the value of b
    // The variable b is split into two, with the first 
    // half being the A register and the second half being the Q register

    int rem = 0; // Q-1 bit
    int num_size = 16; // Size of the registers
    if (b < 0) b += 1 << num_size;

    for (int i = sizeof(int) * 8 / 2; i > 0; i--)
    {   
        // Check if the last two bits are 01 or 10
        if ((b & 1) && !rem) {
            // A - M if Q0Q-1 = 10
            b = b + (-a << num_size);
        } else if (!(b & 1) && rem) {
            // A + M if Q0Q-1 = 01
            b = b + (a << num_size); 
        }
        
        // Get Q-1
        rem = b & 1;
        // Right shift b
        b = b >> 1;
    }

    return b;
}

int main() 
{
    int a = 0;
    int b = 0;

    printf("Enter a (|a|<32768): ");
    scanf("%d",&a);

    printf("Enter b (|b|<32768): ");
    scanf("%d",&b);

    // Since each number is 16 bit long,
    // Magnitude of operand cannot be greater than 2^15
    if (a >= 32768 || b >= 32768 || a <= -32768 || b <= -32768) {
        printf("Please enter numbers less than 2^15\n");
        return -1;
    }

    int expected_val = a * b;
    int booths_val = booth(a, b);

    printf("Answer by Booth's Algorithm: %d\n", booths_val);
    printf("Actual answer: %d\n", expected_val);

}