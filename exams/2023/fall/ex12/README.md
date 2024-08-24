# Τελική Εξέταση #12 - Wordle Themed

Σημαντικό: φροντίζουμε τα προγράμματά μας να είναι ευανάγνωστα, αποδοτικά (σε χώρο και χρόνο) και να έχουν έξοδο όμοια με τα παραδείγματα εκτέλεσης καθώς αυτό είναι μέρος της βαθμολόγησης. Για οποιαδήποτε είσοδο εκτός προδιαγραφών το πρόγραμμα πρέπει να τερματίζει με exit code 1 και αντίστοιχο μήνυμα σφάλματος.

## 1. Γραμμή και Γράμμα (25 Μονάδες)

### Πρόγραμμα: letter.c

Γράψτε ένα πρόγραμμα το οποίο διαβάζει από την πρότυπη είσοδο (stdin) μια σειρά από γραμμές που περιέχουν τα γράμματα μιας λέξης (ένα γράμμα ανά γραμμή με χρήση underscore '_' για όλα τα γράμματα που δεν αποκαλύπτονται σε εκείνη την γραμμή) και τυπώνει στην πρότυπη έξοδο (stdout) την λέξη που δόθηκε. Η είσοδος θα αποτελείται μόνο από λατινικούς (A-Za-z) χαρακτήρες, underscores και αλλαγές γραμμής. Παράδειγμα εκτέλεσης ακολουθεί:

```
$ gcc -o letter letter.c
$ cat reveal.txt
__r_____
_______l
_a______
___n____
_____v__
c_______
______a_
____i___
$ ./letter < reveal.txt
carnival
```

## 2. Προσεγγίζοντας την Λέξη (25 Μονάδες)

### Πρόγραμμα: check.c

Γράψτε ένα πρόγραμμα που να δέχεται ως πρώτο όρισμα μια λέξη στόχο (goal) ακολουθούμενο από μια σειρά από προσπάθειες του χρήστη να μαντέψει την λέξη στόχο και να τυπώνει στην πρότυπη έξοδο την εγγύτητα της κάθε προσπάθειας στην λέξη στόχο. Η εγγύτητα της κάθε λέξης εξαρτάται από δύο μετρικές: (1) πόσα σωστά γράμματα μάντεψε ο χρήστης και είναι σε λάθος θέση και (2) πόσα σωστά γράμματα μάντεψε ο χρήστης και είναι στην σωστή θέση. Όλες οι λέξεις θα αποτελούνται από λατινικούς χαρακτήρες και θα έχουν το ίδιο μήκος. Παραδείγματα εκτέλεσης ακολουθούν:

```
$ gcc -o check check.c
$ ./check unlit legal vinyl sling inlet unlit
legal has 0 correct letters in correct position and 1 correct letters in an incorrect position
vinyl has 0 correct letters in correct position and 3 correct letters in an incorrect position
sling has 0 correct letters in correct position and 3 correct letters in an incorrect position
inlet has 3 correct letters in correct position and 1 correct letters in an incorrect position
unlit has 5 correct letters in correct position and 0 correct letters in an incorrect position
$ ./check hello world worll wrllo
world has 1 correct letters in correct position and 1 correct letters in an incorrect position
worll has 1 correct letters in correct position and 2 correct letters in an incorrect position
wrllo has 3 correct letters in correct position and 0 correct letters in an incorrect position
```

## 3. Κρεμάλα (25 Μονάδες)

### Πρόγραμμα: hangman.c

Γράψτε ένα πρόγραμμα που παίρνει ως πρώτο όρισμα το όνομα ενός αρχείου που περιέχει όλες τις επιτρεπτές λέξεις που μπορεί να βάλει κάποιος (μία ανά γραμμή) και ως δεύτερο όρισμα τα γράμματα της λέξης που έχουμε βρει σε ένα παιχνίδι κρεμάλας και τυπώνει στην πρότυπη έξοδο όλες τις πιθανές λέξεις που μπορεί να ταιριάζουν. Εάν δεν υπάρχει λέξη που να ταιριάζει, το πρόγραμμά σας θα πρέπει να τυπώνει ανάλογο μήνυμα. Παραδείγματα εκτέλεσης ακολουθούν:

```
$ gcc -o hangman hangman.c
$ cat words.txt
cat
DOG
Giraffe
tennis
turtle
$ ./hangman words.txt t_____
tennis
turtle
$ ./hangman words.txt __r___
turtle
$ ./hangman words.txt ___
cat
DOG
$ ./hangman words.txt d__
DOG
$ ./hangman words.txt _e_e__
No words matching guess found
$ ./hangman /usr/share/dict/words __ou________ing
troubleshooting
```

## 4. Εαυτοί Αριθμοί (25 Μονάδες)

### Πρόγραμμα: self.c

Στην θεωρία αριθμών, ένας φυσικός αριθμός $n$ λέγεται εαυτός (self) όταν δεν υπάρχει κάποιος φυσικός αριθμός $m$, έτσι ώστε το $n$ να ισούται με το άθροισμα του $m$ και των ψηφίων του $m$ (με βάση το 10 σε αυτό το θέμα). Έστω $F(n)$ η συνάρτηση που υπολογίζει το άθροισμα ενός φυσικού $n$ και των ψηφίων του. Τότε ένας αριθμός $n$ είναι εαυτός αν και μόνο αν $\nexists m . F(m) = n$. Για παράδειγμα, $F(15) = 15 + 1 + 5 = 21$ και επομένως ο αριθμός 21 δεν είναι εαυτός. Αντίθετα, ο αριθμός 20 είναι εαυτός καθώς δεν υπάρχει φυσικός αριθμός m έτσι ώστε $F(m) = 20$. Υπάρχουν μόλις 13 εαυτοί αριθμοί μικρότεροι του 100:

$$ 1, 3, 5, 7, 9, 20, 31, 42, 53, 64, 75, 86, 97 $$

Γράψτε ένα πρόγραμμα C το οποίο βρίσκει και τυπώνει όλους τους εαυτούς αριθμούς σε ένα εύρος φυσικών αριθμών $[low, high]$ (το εύρος είναι κλειστό, δηλαδή τα άκρα συμπεριλαμβάνονται), όπου οι αριθμοί δίνονται από την γραμμή εντολών. Ακολουθεί παράδειγμα εκτέλεσης για να βρούμε όλους τους εαυτούς αριθμούς στο διάστημα $[9900, 10000]$:

```
$ gcc -o self self.c
$ ./self 9900 10000
Self numbers: 9903 9914 9925 9927 9938 9949 9960 9971 9982 9993
Found 10 total
```