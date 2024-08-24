# Τελική Εξέταση #2 - Pokémon Themed

Σημαντικό: φροντίζουμε τα προγράμματά μας αν είναι ευανάγνωστα, αποδοτικά (σε χώρο και χρόνο) και να έχουν έξοδο όμοια με τα παραδείγματα εκτέλεσης καθώς αυτό είναι μέρος της βαθμολόγησης. Για οποιαδήποτε είσοδο εκτός προδιαγραφών το πρόγραμμα πρέπει να τερματίζει με exit code 1 και αντίστοιχο μήνυμα σφάλματος.


## 1. Pikaκίστικα (25 Μονάδες)

### Πρόγραμμα: pika.c

Γράψτε ένα πρόγραμμα που διαβάζει το κείμενο που δίνεται από την πρότυπη είσοδο (stdin) και τυπώνει την κάθε λέξη χαρακτήρα στην πρότυπη έξοδο (stdout) με το πρόθεμα "pika". Οι λέξεις χωρίζονται με κενούς (whitespace) χαρακτήρες. Αριθμοί ή σημεία στίξης *δεν* θεωρούνται λέξεις. Παράδειγμα εκτέλεσης:

```
$ cat ash.txt
	I wanna be the very best�,
	Like no one ever was ,
	To catch them is my real-test ,
	To train them is my cause !
$ ./pika  < ash.txt
	pikaI pikawanna pikabe pikathe pikavery pikabest�,
	pikaLike pikano pikaone pikaever pikawas ,
	pikaTo pikacatch pikathem pikais pikamy pikareal-test ,
	pikaTo pikatrain pikathem pikais pikamy pikacause !
```

## 2. Τουρνουά (25 Μονάδες)

### Πρόγραμμα: tournament.c

Γράψτε ένα πρόγραμμα που δέχεται ως ορίσματα όλα τα pokémon που διαγωνίζονται στο τουρνουά και στην συνέχεια τυπώνει στην πρότυπη έξοδο όλους τους αγώνες που θα γίνουν. Κάθε pokémon πρέπει να παίξει με κάθε άλλο ακριβώς δύο φορές. Παράδειγμα εκτέλεσης ακολουθεί:

```bash
$ ./tournament charmander dratini mew
charmander vs dratini
charmander vs mew
dratini vs charmander
dratini vs mew
mew vs charmander
mew vs dratini
```

## 3. Μίνι Βάση Δεδομένων (25 Μονάδες)

### Πρόγραμμα: pokedex.c

Γράψτε ένα πρόγραμμα που παίρνει δύο ορίσματα: (1) το όνομα του αρχείο που περιέχει όλα τα pokémon που έχουμε πιάσει με όλα τα δεδομένα τους και (2) την ημερομηνία που αναζητούμε και επιστρέφει αναλυτικές πληροφορίες για όλα τα pokémon που πιάστηκαν *μετά* από εκείνη την ημερομηνία ταξινομημένα. Παράδειγμα εκτέλεσης ακολουθεί:

```bash
$ cat pokedex.db
name, date_caught, level
geodude, 15-02-2024, 15
slowpoke, 16-01-2024, 20
pidgeotto, 19-02-2024, 5
bulbasaur, 01-01-2005, 37
onix, 31-07-2021, 21
gyarados, 20-12-2018, 19
$ gcc -o pokedex pokedex.c
$ ./pokedex pokedex.db 19-02-2024
pidgeotto was caught on 19-02-2024 and is level 5
$ ./pokedex pokedex.db 01-01-2024
slowpoke was caught on 16-01-2024 and is level 20
geodude was caught on 15-02-2024 and is level 15
pidgeotto was caught on 19-02-2024 and is level 5
```

## 4. Ανεβαίνοντας Επίπεδο (25 Μονάδες)

### Πρόγραμμα: levelup.c

Ένα pokémon μπορεί να ανέβει 1, 2 ή 3 επίπεδα σε κάθε αγώνα ανάλογα με το πόσο δύσκολος είναι ο αντίπαλος (εύκολος, μεσαίος, δύσκολος). Γράψτε ένα πρόγραμμα που παίρνει ένα επίπεδο "στόχο" ως όρισμα και τυπώνει στην πρότυπη έξοδο με πόσους διαφορετικούς τρόπους μπορεί να φτάσει σε αυτό.  Έστω ότι θέλουμε να φτάσουμε στο επίπεδο 5. Ένας τρόπος να φτάσουμε είναι 1-1-1-1-1, δηλαδή να κερδίσουμε 5 εύκολους αντιπάλους. Ένας άλλος είναι ο 2-2-1 (δύο μεσαίους και μετά έναν εύκολο). Άλλοι πιθανοί τρόποι είναι οι 3-2, 2-3, 3-1-1, κ.ο.κ - σε κάθε περίπτωση θέλουμε να φτάσουμε *ακριβώς* στο επίπεδο στόχο. Παραδείγματα εκτελέσεων ακολουθούν:

```bash
$ gcc -o levelup.c levelup
$ ./levelup 3
There are 4 different ways to reach level 3
$ ./levelup 5
There are 13 different ways to reach level 5
$ ./levelup 6
There are 24 different ways to reach level 6
$ ./levelup 50
There are 10562230626642 different ways to reach level 50
```

