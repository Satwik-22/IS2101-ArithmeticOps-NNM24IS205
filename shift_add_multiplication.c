#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to print binary with leading zeros
void print_binary(int num, int bits) {
    for (int i = bits - 1; i >= 0; i--) {
        printf("%d", (num >> i) & 1);
    }
}

// Shift-Add Multiplication (hardware simulation)
int shift_add_multiply(int multiplicand, int multiplier, int bits) {
    int A = 0;                      // Accumulator (same size as multiplicand)
    int Q = multiplier;             // Multiplier register
    int M = multiplicand;           // Multiplicand register
    int Qn = 0;                     // Extra bit (like Q-1 in hardware)
    int total_bits = bits * 2;      // To show full result

    printf("\n====== Shift-Add Multiplication ======\n");
    printf("Multiplicand (M) = %d, Multiplier (Q) = %d\n", M, Q);
    printf("------------------------------------------------------\n");
    printf("Step |       A       |       Q       | Qn |  Action\n");
    printf("------------------------------------------------------\n");

    for (int step = 0; step < bits; step++) {
        // Step 1: Check Q0
        if (Q & 1) {
            A = A + M;  // Add M to A
            printf("  %d  |     ", step + 1);
            print_binary(A, bits);
            printf("     |     ");
            print_binary(Q, bits);
            printf("     |  %d | A = A + M\n", Qn);
        } else {
            printf("  %d  |     ", step + 1);
            print_binary(A, bits);
            printf("     |     ");
            print_binary(Q, bits);
            printf("     |  %d | No addition\n", Qn);
        }

        // Step 2: Shift right (Arithmetic Shift)
        Qn = Q & 1;  // Store Q0 before shifting
        Q = (Q >> 1) | ((A & 1) << (bits - 1));
        A = A >> 1;
    }

    int result = (A << bits) | (Q & ((1 << bits) - 1));
    printf("------------------------------------------------------\n");
    printf("Final Result (in decimal): %d\n", result);
    printf("Final Result (binary %d bits): ", total_bits);
    print_binary(result, total_bits);
    printf("\n");

    return result;
}

int main() {
    int multiplicand, multiplier, bits;

    printf("Enter multiplicand: ");
    scanf("%d", &multiplicand);
    printf("Enter multiplier: ");
    scanf("%d", &multiplier);
    printf("Enter bit size : ");
    scanf("%d", &bits);

    shift_add_multiply(multiplicand, multiplier, bits);

    return 0;
}
