# Τελική Εξέταση #11 - Pacman Themed

Σημαντικό: φροντίζουμε τα προγράμματά μας να είναι ευανάγνωστα, αποδοτικά (σε χώρο και χρόνο) και να έχουν έξοδο όμοια με τα παραδείγματα εκτέλεσης καθώς αυτό είναι μέρος της βαθμολόγησης. Για οποιαδήποτε είσοδο εκτός προδιαγραφών το πρόγραμμα πρέπει να τερματίζει με exit code 1 και αντίστοιχο μήνυμα σφάλματος.

## 1. Αναζητώντας τον Blinky (25 Μονάδες)

### Πρόγραμμα: blinky.c

Γράψτε ένα πρόγραμμα το οποίο διαβάζει κείμενο από την πρότυπη είσοδο (stdin) και το τυπώνει στην πρότυπη έξοδο (stdout) με τους εξής περιορισμούς:
1. Κάθε φορά που βρίσκει την λέξη Blinky - να την τοποθετεί ανάμεσα σε αστεράκια '*' και να την κάνει να αναβοσβήνει (blink).
1. Αν το string Blinky είναι μέρος άλλης λέξης δεν χρειάζεται κάποια αλλαγή.
1. Οι λέξεις αποτελούνται μόνο από λατινικούς χαρακτήρες (A-Za-z) οποιοσδήποτε άλλος χαρακτήρας θεωρείται διαχωριστικό λέξεων.

Παράδειγμα εκτέλεσης ακολουθεί:

[![asciicast](https://asciinema.org/a/js20ZyFDDS0t8ocszkBBo6b4J.svg)](https://asciinema.org/a/js20ZyFDDS0t8ocszkBBo6b4J)

Αν για κάποιο λόγο δεν παίζει το παραπάνω link:

```
$ gcc -o blinky blinky.c
$ cat description.txt
In the Pac-Man universe, Blinky is the red ghost who
persistently chases the game's hero, earning the
nickname "Shadow" for his relentless pursuit.
Blinky's strategy intensifies as Pac-Man consumes
more dots, making Blinky a formidable challenge and
a central figure in game strategy. His vivid red hue
not only marks Blinky as the primary antagonist but
also signals the immediate threat he poses.
$ ./blinky < description.txt
In the Pac-Man universe, *Blinky* is the red ghost who
persistently chases the game's hero, earning the
nickname "Shadow" for his relentless pursuit.
*Blinky*'s strategy intensifies as Pac-Man consumes
more dots, making *Blinky* a formidable challenge and
a central figure in game strategy. His vivid red hue
not only marks *Blinky* as the primary antagonist but
also signals the immediate threat he poses.
```

## 2. Τοποθέτηση του Pacman (25 Μονάδες)

### Πρόγραμμα: position.c

Γράψτε ένα πρόγραμμα που παίρνει ως πρώτο όρισμα την διάσταση ενός τετραγωνικού πλέγματος και ως υπόλοιπα ορίσματα τις θέσεις των φαντασμάτων (ghosts) του pacman και τυπώνει όλες τις θέσεις στο πλέγμα που θα μπορούσε να τοποθετηθεί ο pacman. Ο pacman δεν μπορεί να τοποθετηθεί στην ίδια γραμμή ή στήλη με κάποιο φάντασμα. Όλες οι διαστάσεις δίνονται ως "x,y" ορίσματα (όπου x, y είναι ακέραιοι). Εάν δεν υπάρχει δυνατή τοποθέτηση το πρόγραμμά σας θα πρέπει να τυπώνει ανάλογο μήνυμα. Παραδείγματα εκτέλεσης ακολουθούν:

```
$ gcc -o position position.c
$ ./position 4 0,4 3,2 2,1 1,3
Pacman cannot be positioned anywhere
$ ./position 4 0,4 3,2 2,1 0,3
Pacman can be positioned at: 1,0
$ ./position 4 0,4 3,2 2,1
Pacman can be positioned at: 1,0
Pacman can be positioned at: 1,3
$ ./position 4 1,2 2,1
Pacman can be positioned at: 0,0
Pacman can be positioned at: 0,3
Pacman can be positioned at: 3,0
Pacman can be positioned at: 3,3
```

## 3. Κινήσεις σε Πλέγμα (25 Μονάδες)

### Πρόγραμμα: pacman.c

Γράψτε ένα πρόγραμμα που παίρνει δύο ορίσματα: (1) το όνομα ενός αρχείου που περιέχει μια πίστα pacman και (2) τις κινήσεις που πρέπει να κάνει ο pacman πάνω στο πλέγμα και τυπώνει την τελική κατάσταση του παιχνιδιού μετά από αυτές τις κινήσεις. Το αρχείο θα έχει την ακόλουθη μορφή:
1. Διάσταση του πλέγματος του παιχνιδιού (δεκαδικός ακέραιος).
2. Τετράγωνο πλέγμα με χαρακτήρες '.' και ένα 'P' για την αρχική θέση του pacman. Όλοι οι άλλοι χαρακτήρες αγνοούνται.
Οι κινήσεις που πρέπει να κάνει ο pacman θα αποτελούνται από 4 χαρακτήρες 'U' (Up), 'D' (Down), 'L' (Left), 'R' (Right). Όταν ο pacman κινείται σε κάποια θέση, τότε η τελεία ('.') σε εκείνη την θέση εξαφανίζεται. Η πίστα είναι τόρος, δηλαδή αν είσαι στην τελευταία γραμμή της και κινηθείς προς τα κάτω (D) τότε μεταφέρεσαι στην πρώτη γραμμή. Αντίστοιχα για κινήσεις αριστερά-δεξιά. Παραδείγματα εκτέλεσης ακολουθούν:

```
$ gcc -o pacman pacman.c
$ cat level.txt
7
.......
.......
..P....
.......
.......
.......
.......
$ ./pacman level.txt RRD
.......
.......
..   ..
....P..
.......
.......
.......
$ ./pacman level.txt RRDDLL
.......
.......
..   ..
.... ..
..P  ..
.......
.......
$ ./pacman level.txt RRDDLLUU
.......
.......
..P  ..
.. . ..
..   ..
.......
.......
$ ./pacman level.txt RRDDLLUULLLL
.......
.......
     P
.. . ..
..   ..
.......
.......

```

## 4. Clyde Πρώτοι (25 Μονάδες)

### Πρόγραμμα: clyde.c

Ένας ακέραιος λέγεται πρώτος όταν διαιρείται μόνο με τον εαυτό του και την μονάδα. Ένας πρώτος λέγεται clyde πρώτος όταν υπάρχει μια περιστροφή των ψηφίων του (με βάση το 10) που είναι επίσης πρώτος. Γράψτε ένα πρόγραμμα που παίρνει έναν ακέραιο από την κονσόλα και αποφαίνεται αν είναι Clyde πρώτος ή όχι. Παραδείγματα εκτέλεσης:

```
$ gcc -o clyde clyde.c -lm
$ ./clyde 13
13 is a clyde prime because 31 is prime too
$ ./clyde 99923
99923 is a clyde prime because 92399 is prime too
$ ./clyde 41
41 is NOT a clyde prime
$ ./clyde 99924
99924 is NOT a clyde prime
$ ./clyde 90000520793
90000520793 is a clyde prime because 93900005207 is prime too
```
