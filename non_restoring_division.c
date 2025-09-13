#include <stdio.h>

// Function to print binary with leading zeros
void print_binary(int num, int bits) {
    for (int i = bits - 1; i >= 0; i--) {
        printf("%d", (num >> i) & 1);
    }
}

// Print Q with optional blank (_) for LSB
void print_Q_with_blank(int Q, int bits, int blank) {
    for (int i = bits - 1; i >= 1; i--) {
        printf("%d", (Q >> i) & 1);
    }
    if (blank)
        printf("_");  // blank space for LSB
    else
        printf("%d", Q & 1);
}

// Non-Restoring Division Algorithm (with step trace)
void non_restoring_division(int dividend, int divisor, int n) {
    int A = 0;                 // Accumulator / Remainder
    int Q = dividend;          // Dividend (Quotient Register)
    int M = divisor;           // Divisor
    int count = n;             // Number of bits
    int Qo;                    // Decision bit

    printf("\n--- Non-Restoring Division Algorithm ---\n");
    printf("Dividend = %d, Divisor = %d\n\n", dividend, divisor);

    // Table header
    printf("Step | Operation             | Qo |       A       |       Q\n");
    printf("-----------------------------------------------------------------\n");

    // Initial values
    printf("  0  | Initial               | -- |      ");
    print_binary(A, n);
    printf("     |      ");
    print_binary(Q, n);
    printf("\n");

    while (count > 0) {
        int step = n - count + 1;

        // Step 1: Shift left (A,Q)
        A = (A << 1) | ((Q >> (n - 1)) & 1);
        Q = (Q << 1) & ((1 << n) - 1);   // leave space at LSB

        printf(" %2d  | Shift Left            | -- |      ", step);
        print_binary(A, n);
        printf("     |      ");
        print_Q_with_blank(Q, n, 1);
        printf("\n");

        // Step 2: If A >= 0 → A = A - M, else A = A + M
        if (A >= 0) {
            A = A - M;
            printf(" %2d  | A>=0: Subtract M      | -- |      ", step);
        } else {
            A = A + M;
            printf(" %2d  | A<0: Add M            | -- |      ", step);
        }
        print_binary(A, n);
        printf("     |      ");
        print_Q_with_blank(Q, n, 1);
        printf("\n");

        // Step 3: Decision bit Qo
        if (A >= 0) {
            Qo = 1;
        } else {
            Qo = 0;
        }
        Q = (Q & ~1) | Qo;

        printf(" %2d  | Decision -> Qo=%d      | %d  |      ", step, Qo, Qo);
        print_binary(A, n);
        printf("     |      ");
        print_binary(Q, n);
        printf("\n");

        count--;
    }

    // Final correction (if A < 0, add M back)
    if (A < 0) {
        A = A + M;
    }

    printf("-----------------------------------------------------------------\n");
    printf("Final Quotient (Q)  = "); print_binary(Q, n); printf(" = %d\n", Q);
    printf("Final Remainder (A) = "); print_binary(A, n); printf(" = %d\n", A);
    printf("\nCheck: %d = %d * %d + %d\n", dividend, divisor, Q, A);
}

int main() {
    int dividend, divisor, bits;

    printf("Enter dividend: ");
    scanf("%d", &dividend);
    printf("Enter divisor: ");
    scanf("%d", &divisor);
    printf("Enter number of bits to simulate: ");
    scanf("%d", &bits);

    non_restoring_division(dividend, divisor, bits);

    return 0;
}
