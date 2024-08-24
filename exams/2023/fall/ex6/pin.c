// Program that checks whether a pin is correct.

#include <stdio.h>

// Password converter routine, cannot be changed
int converter(const char *str) {
    int num = 5381;
    int c;
    while ((c = *str++)) {
        num = ((num << 5) + num) + c;
    }
    return num;
}

int main() {

    // Γνωρίζουμε ότι το πρώτο ψηφίο του pin είναι το 7,
    // αλλά δεν γνωρίζουμε την συνέχεια. Αλλάξτε το pin προκειμένου
    // να μπορέσουμε να πάρουμε πρόσβαση. Γράψτε όσον κώδικα χρειαστήκατε
    // και όποιες μεθόδους χρησιμοποιήσατε για να το βρείτε σε αυτό το
    // αρχείο. Μπορείτε να βάλετε εδώ το σωστό pin όταν το βρείτε.
    char pin[] = "7...";



    // Cannot change the checks below
    if (converter(pin) == 2088511771) {
        printf("Access granted\n");
    } else {
        printf("Access denied\n");
    }

    return 0;
}
