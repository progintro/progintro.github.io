#include <stdio.h>

int main() {
    long long int costleft, costright;
    // Με την εντολή while(1) εξασφαλίζω ότι η επανάληψή μου θα σταματήσει μόλις συμβεί το EOF (ctrl + D)
    while(1){
        printf("Please enter the cost of going left: ");
        if(scanf("%lld", &costleft) == 1){ // αυτή η σύνταξη μας επιτρέπει να ελέγξουμε εάν δόθηκε έγκυρη τιμή εισόδου
            printf("Please enter the cost of going right: ");
            if(scanf("%lld", &costright) == 1){
                // Σε αυτό το σημείο ο χρήστης έχει εισάγει επιτυχώς τα δύο κόστη και 
                // γίνεται η σύγκρισή τους ώστε να φανεί το αντίστοιχο μήνυμα
                if(costright<costleft){
                    printf("Go right.\n");
                } else {
                    printf("Go left.\n");
                }
            } else {
                // Εάν ο χρήστης δεν δώσει δεξί κόστος, τότε εμφανίζεται το παρακάτω 
                // μήνυμα και η συνάρτηση main επιστρέφει την τιμή 0, διότι θεωρείται σφάλμα
                printf("No right cost provided.\n");
                return 1;
            }
        }
        else {
            // Εάν ο χρήστης δεν δώσει left cost, ή το input δεν είναι έγκυρο, τότε εμφανίζεται το ακόλουθο μήνυμα
            printf("Terminating.\n");
            return 0;
        }
    }
}