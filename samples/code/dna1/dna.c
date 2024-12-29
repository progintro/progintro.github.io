/*
Φοιτήτρια: Ματίνα Ναδάλη
Καθηγητής: Αυγερινός Αθανάσιος
Μάθημα: Εισαγωγή στον προγραμματισμό
Πρόγραμμα dna.c : Εκτυπώνει την μέγιστη κοινή αλυσίδα DNA ανάμεσα σε δύο
δείγματα
*/

#include <stdio.h>
#include <stdlib.h>
int dna1_length, dna2_length;
int max_length = 0;
int starting_index = 0;  //η θέση του πρώτου στοιχείου της μέγιστης κοινής ακολουθίας στο dna1

//ελέγχει αν ο χαρακτήρας είναι κάποια έγκυρη βάση
int is_base(char character) {
  return character == 'A' || 
         character == 'C' || 
         character == 'G' ||
         character == 'T';
}

//θέτει τη global μεταβλητή starting_index στο index του χαρακτήρα του dna1, από
//τον οποίο αρχίζει η μέγιστη κοινή ακολουθία σχόλιο 2 στο README.md
void find_longest_common_sequence(int *common_suffixes, int dna2_index,char *dna1, char *dna2) {
  //συνθήκη τερματισμού - δεν υπάρχουν άλλες βάσεις στο dna2 για να συγκριθούν
  if (dna2_index < 0) {
    free(common_suffixes);
    return;
  }
  //δεσμεύει μνήμη για τα νέα μήκη των μέγιστων κοινών καταλήξεων - όλες οι
  //τιμές αρχικοποιούνται στο 0
  int *new_common_suffixes = calloc(dna1_length, sizeof(int));
  for (int i = 0; i < dna1_length; i++) {
    if (dna1[i] == dna2[dna2_index]) {
      //βρέθηκε νέος κοινός χαρακτήρας - η κοινή ακολουθία συνεχίζεται και το
      //μήκος της αυξάνεται κατά 1
      new_common_suffixes[i] = 1;
      if (i < dna1_length - 1) {
        new_common_suffixes[i] += common_suffixes[i + 1];
      }
      //ανανεώνει το μέγιστο μήκος της κοινής ακολουθίας και το starting_index
      if (new_common_suffixes[i] > max_length) {
        max_length = new_common_suffixes[i];
        starting_index = i;
      }
    }
  }
  //ελευθέρωνει τη μνήμη για τα προηγούμενα μήκη των κοινών καταλήξεων
  free(common_suffixes);
  //ξανακαλεί τη συνάρτηση για τον προηγούμενο χαρακτήρα του dna2
  find_longest_common_sequence(new_common_suffixes, dna2_index - 1, dna1, dna2);
}

int main(int argc, char **argv) {
  //ελέγχει τον αριθμό των ορισμάτων
  if (argc != 3) {
    perror("Error: arguments missing. Usage: ./dna dnafile1 dnafile2");
    exit(1);
  }
  FILE *dna1_in = fopen(argv[1], "r");
  FILE *dna2_in = fopen(argv[2], "r");
  if (!dna1_in || !dna2_in) {
    perror("Error: Could not open files");
    exit(1);
  }
  //δεσμεύει μνήμη στο σωρό για την αποθήκευση των ακολουθιών DNA - χρησιμοποιεί
  //το μέγιστο δυνατό μήκος
  char *dna1 = malloc(100000 * sizeof(char));
  char *dna2 = malloc(100000 * sizeof(char));
  if (!dna1 || !dna2) {
    perror("Memory allocation failed");
    exit(1);
  }
  char new_character;

  //διαβάζει τους χαρακτήρες από τα αρχεία και τα καταχωρεί στους αντίστοιχους
  //πίνακες μόνο αν αντιστοιχούν σε έγκυρη βάση
  while (fscanf(dna1_in, "%c", &new_character) != EOF) {
    if (is_base(new_character)) {
      dna1[dna1_length] = new_character;
      dna1_length++;
    }
  }
  while (fscanf(dna2_in, "%c", &new_character) != EOF) {
    if (is_base(new_character)) {
      dna2[dna2_length] = new_character;
      dna2_length++;
    }
  }

  //δεσμεύει μνήμη για να αποθηκεύσει τα μήκη των μέγιστων ακολουθιών που
  //περιέχουν κάθε χαρακτήρα του dna1 η δέσμευση γίνεται με την calloc ώστε οι
  //τιμές να αρχικοποιηθούν στο 0
  int *common_suffixes = calloc(dna1_length, sizeof(int));

  for (int i = 0; i < dna1_length; i++) {
    if (dna1[i] == dna2[dna2_length - 1]) {
      common_suffixes[i] = 1;
    }
  }
  find_longest_common_sequence(common_suffixes, dna2_length - 2, dna1, dna2);

  //εκτυπώνει τη μέγιστη κοινή ακολουθία
  for (int i = starting_index; i < starting_index + max_length; i++) {
    printf("%c", dna1[i]);
  }
  printf("\n");
  //απελευθερώνει τη δεσμευμένη μνήμη
  free(dna1);
  free(dna2);

  fclose(dna1_in);
  fclose(dna2_in);
  return 0;
}
