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

int rec_div(int q, int m)
{
    // Logic:
    // All operations are done in b itself
    // Here both A & Q register vals are stored in Q
    // Both numbers are considered 16 bit long

    int num_size = 16; // Size of the registers
    int temp = 0;

    for (int i = sizeof(int) * 8 / 2; i > 0; i--)
    {   
        temp = 0;  // Temperary variable for storage of 

        q = q << 1;
        
        if ((m >> 31) ^ (q >> 31)) {
            // If MSB of m and q are different
            temp = q + (m << num_size);
        } else {
            // If MSB of m and q are same
            temp = q + (-m << num_size);
        }
        if ((temp >> 31) == (q >> 31)) {
            q = temp | 1;
            // If the sign of the result is same as the sign of q
            // Set the LSB of q to 1
            // Else no restore A
        }
    }

    return q;
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

    int ch = 0;
    printf("Enter 1 for multiplication, 2 for division: ");
    scanf("%d", &ch);
    if (ch != 2 && ch != 1) {
        printf("Invalid choice\n");
        return -1;
    }

    if (ch == 1) {
        int expected_val = a * b;
        int booths_val = booth(a, b);
        printf("Answer by Booth's Algorithm: %d\n", booths_val);
        printf("Actual answer: %d\n", a * b);
    } 
    else 
    {
        int expected_qut = a / b;
        int expected_rem = a % b;
        int div_val = rec_div(a, b);
        // Get the quotient and remainder

        // Truncating top 16 bits to retrieve the quotient
        int div_qut = div_val & 65535;
        if ((a < 0 && b > 0) || (a > 0 && b < 0)) {
            div_qut = -div_qut;
        }
        // Shifting bits to retrieve the remainder
        int div_rem = div_val >> 16;

        printf("Answer by Booth's Algorithm: (Quotient: %d) (Remainder: %d)\n", div_qut, div_rem);
        printf("Actual answer: (Quotient: %d) (Remainder: %d)\n", expected_qut, expected_rem);
    }
    

}