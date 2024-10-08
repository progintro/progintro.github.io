# Τελική Εξέταση #9 - LOTR Themed

Σημαντικό: φροντίζουμε τα προγράμματά μας να είναι ευανάγνωστα, αποδοτικά (σε χώρο και χρόνο) και να έχουν έξοδο όμοια με τα παραδείγματα εκτέλεσης καθώς αυτό είναι μέρος της βαθμολόγησης. Για οποιαδήποτε είσοδο εκτός προδιαγραφών το πρόγραμμα πρέπει να τερματίζει με exit code 1 και αντίστοιχο μήνυμα σφάλματος.

## 1. Έλεγχος Εκτελέσιμου (25 Μονάδες)

### Πρόγραμμα: elf.c

Γράψτε ένα πρόγραμμα που παίρνει ως όρισμα το όνομα ενός αρχείου και αποφαίνεται για το αν το αρχείο είναι ένα Linux εκτελέσιμο ELF (Executable and Linking Format) ή όχι. Ένα αρχείο θεωρείται ELF όταν ξεκινάει με τους χαρακτήρες 0x7f, E, L, F. Οποιοδήποτε άλλο αρχείο δεν θεωρείται ELF. Παραδείγματα εκτέλεσης ακολουθούν:

```
$ gcc -o elf elf.c
$ ./elf foo
Error: Unable to read file
$ ./elf message.txt
message.txt is NOT an ELF file.
$ ./elf ./elf.c
./elf.c is NOT an ELF file.
$ ./elf ./elf
./elf is an ELF file.
$ ./elf /bin/ls
/bin/ls is an ELF file.
$ ./elf /lib/x86_64-linux-gnu/libc.so.6
/lib/x86_64-linux-gnu/libc.so.6 is an ELF file.
```

## 2. Πετυχαίνοντας τον Στόχο (25 Μονάδες)

### Πρόγραμμα: legolas.c

Γράψτε ένα πρόγραμμα το οποίο παίρνει ως ορίσματα από την γραμμή εντολών έναν ακέραιο-στόχο (goal) και στην συνέχεια ένα σύνολο υποψηφίων ακεραίων (candidates) και τυπώνει όλους τους συνδυασμούς 3 υποψηφίων των οποίων το άθροισμα ισούται με τον στόχο. Η σειρά με την οποία εκτυπώνονται τα αποτελέσματα δεν έχει σημασία για την ορθότητα του προγράμματος. Παραδείγματα εκτέλεσης ακολουθούν:

```
$ gcc -o legolas legolas.c
$ ./legolas 42 19 21 3 5 12
No combination of candidates leads to 42
$ ./legolas 42 19 21 3 5 12 11
Candidates combination found: 19 + 12 + 11 = 42
$ ./legolas 42 27 25 12 31 5 26 40 34 3 18
Candidates combination found: 27 + 12 + 3 = 42
Candidates combination found: 25 + 12 + 5 = 42
Candidates combination found: 5 + 34 + 3 = 42
$ ./legolas 37372082074 9238742398 82934723 27893492387 127863435 239847289
Candidates combination found: 9238742398 + 27893492387 + 239847289 = 37372082074

```

## 3. Πολύτιμοι Πίνακες (25 Μονάδες)

### Πρόγραμμα: precious.c

Ένας πίνακας ακεραίων λέγεται πολύτιμος όταν το άθροισμα των στοιχείων της κάθε γραμμής ισούται με το άθροισμα των στοιχείων της κάθε στήλης. Γράψτε ένα πρόγραμμα που δέχεται το όνομα ενός αρχείου που περιέχει έναν πίκανα ως πρώτο όρισμα και τυπώνει εάν ο πίνακας είναι πολύτιμος. Το αρχείο που περιέχει τον πίνακα ξεκινά με τις διαστάσεις του πίνακα και συνεχίζει με τους ακεραίους που αποτελούν τα στοιχεία του. Παραδείγματα εκτέλεσης ακολουθούν:

```
$ gcc -o precious precious.c
$ cat ring.txt
3 3
8 1 6
3 5 7
4 9 2
$ ./precious ring.txt
My precious!
$ cat not-ring.txt
3 4
6 1 6 2
7 5 1 2
4 9 8 9
$ ./precious not-ring.txt
This matrix is NOT precious.
```

Για παράδειγμα ο πρώτος πίνακας είναι πολύτιμος καθώς κάθε γραμμή και κάθε στήλη αθροίζει στον ίδιο ακέραιο (το 15).

## 4. Κάδρο (25 Μονάδες)

### Πρόγραμμα: frame.c

Γράψτε ένα πρόγραμμα που διαβάζει από την πρότυπη είσοδο (stdin) ένα κείμενο λατινικών χαρακτήρων και το τυπώνει στην πρότυπη έξοδο (stdout) εντός ενός τετράγωνου κάδρου. Το κάδρο αποτελείται από τον χαρακτήρα '*' (42 στο δεκαδικό). Το πρόγραμμά σας πρέπει να μπορεί να χειριστεί οποιονδήποτε αριθμό γραμμών κάθε μία από τις οποίες μπορεί να είναι οποιουδήποτε μεγέθους. Παράδειγμα εκτέλεσης ακολουθεί:

```
$ cat message.txt
    One Ring to
   Rule them all
    One Ring to
     find them
    One Ring to
   Bring them all
and in the darkness
    Bind them
$ gcc -o frame frame.c
$ ./frame < message.txt
*********************
*    One Ring to    *
*   Rule them all   *
*    One Ring to    *
*     find them     *
*    One Ring to    *
*   Bring them all  *
*and in the darkness*
*    Bind them      *
*********************
```
