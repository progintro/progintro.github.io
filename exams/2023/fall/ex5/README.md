# Τελική Εξέταση #5 - HP Themed

Σημαντικό: φροντίζουμε τα προγράμματά μας να είναι ευανάγνωστα, αποδοτικά (σε χώρο και χρόνο) και να έχουν έξοδο όμοια με τα παραδείγματα εκτέλεσης καθώς αυτό είναι μέρος της βαθμολόγησης. Για οποιαδήποτε είσοδο εκτός προδιαγραφών το πρόγραμμα πρέπει να τερματίζει με exit code 1 και αντίστοιχο μήνυμα σφάλματος.


## 1. Αναποδογύρισμα (25 Μονάδες)

### Πρόγραμμα: flip.c

Γράψτε ένα πρόγραμμα που διαβάζει το κείμενο που δίνεται από την πρότυπη είσοδο (stdin) και τυπώνει την κάθε γραμμή στην πρότυπη έξοδο (stdout) αντίστροφα, δηλαδή τυπώνοντας τους χαρακτήρες όπως θα διαβάζονταν από τα δεξιά προς τα αριστερά. Παράδειγμα εκτέλεσης:

```
$ gcc -o flip flip.c
$ cat riddle.txt
, esiugsid ni sevil ohw nosrep eht fo kniht tsriF
. seil tub thguan sllet dna sterces ni slaed ohW
, dnem ot gniht tsal eht syawla s'tahw em llet ,txeN
? dne eht fo dne dna elddim fo elddim ehT
 draeh netfo dnuos eht em evig yllanif dnA
� drow dnif-ot-drah a rof hcraes eht gniruD
, siht em rewsna dna ,rehtegot meht gnirts woN
? ssik ot gnilliwnu eb uoy dluow erutaerc hcihW
$ ./flip < riddle.txt
First think of the person who lives in disguise ,
Who deals in secrets and tells naught but lies .
Next, tell me what's always the last thing to mend ,
The middle of middle and end of the end ?
And finally give me the sound often heard
During the search for a hard-to-find word �
Now string them together, and answer me this ,
Which creature would you be unwilling to kiss ?
```

## 2. Μαγικό Ζευγάρι (25 Μονάδες)

### Πρόγραμμα: magicpair.c

Δύο θετικοί ακέραιοι αποτελούν μαγικό ζευγάρι εάν αποτελούνται από τα ίδια ψηφία αλλά πιθανόν με διαφορετική σειρά. Για παράδειγμα, οι αριθμοί 1980 και 1908 αποτελούν ένα μαγικό ζευγάρι, ενώ οι αριθμοί 1980 και 198 δεν είναι. Γράψτε ένα πρόγραμμα που δέχεται ακεραίους σε δεκαδική μορφή ως ορίσματα και τυπώνει αν οι αριθμοί αποτελούν ένα μαγικό ζευγάρι. Παραδείγματα εκτέλεσης:

```
$ ./magicpair 1980 1908
1980 and 1908 are a magic pair.
$ ./magicpair 1980 198
Not a magic pair
$ ./magicpair -18 -18
Not a magic pair
$ ./magicpair 4321 1234
4321 and 1234 are a magic pair.
$ ./magicpair 4231444232 3244214243
4231444232 and 3244214243 are a magic pair.
```

## 3. Επιλογή (25 Μονάδες)

### Πρόγραμμα: sorting.c

Γράψτε ένα πρόγραμμα το οποίο παίρνει ως όρισμα το όνομα ενός αρχείου που περιέχει ονόματα παιδιών και το σκορ ταιριάσματος του κάθε παιδιού με έναν κοιτώνα του Hogwarts. Κάθε γραμμή περιέχει ακριβώς ένα όνομα ακολουθούμενο από παύλα (dash -) και από το σκορ ταιριάσματος (ένας αριθμός κινητής υποδιαστολής από το 0 μέχρι το 5). Η αντιστοιχία έχει ως εξής: 1 -> Gryffindor, 2 -> Hufflepuff, 3 -> Ravenclaw, 4 -> Slytherin. Το πρόγραμμα πρέπει να τυπώνει στην πρότυπη έξοδο το κάθε όνομα ακολουθούμενο από το όνομα του κοιτώνα που ταιριάζει καλύτερα. Παράδειγμα εκτέλεσης ακολουθεί:

```
$ cat names.txt
Harry Potter - 1.01
Hermione Granger - 1
Draco Malfoy - 4.9
Cho Chang - 3.5
Cedric Diggory - 1.50001
Luna Lovegood - 2.76
$ gcc -o sorting sorting.c
$ ./sorting names.txt
Harry Potter -> Gryffindor
Hermione Granger -> Gryffindor
Draco Malfoy -> Slytherin
Cho Chang -> Ravenclaw
Cedric Diggory -> Hufflepuff
Luna Lovegood -> Ravenclaw
```



## 4. Μεταμορφώσιμες Προτάσεις (25 Μονάδες)

### Πρόγραμμα: meta.c

Γράψτε ένα πρόγραμμα που παίρνει 2 προτάσεις ως ορίσματα από την γραμμή εντολών και τυπώνει αν η μία πρόταση μπορεί να μεταμορφωθεί στην άλλη κάνοντας αντικαταστάσεις λέξεων καθώς και ποιες αντικαταστάσεις απαιτούνται. Για να μπορεί να μεταμορφωθεί μια πρόταση σε μια δεύτερη πρέπει *όλες* οι λέξεις της πρώτης να ταιριάξουν με λέξεις της δεύτερης μία προς μία. Οι προτάσεις θα έχουν μόνο κενά και λατινικούς χαρακτήρες (A-Z, a-z). Παραδείγματα εκτέλεσης ακολουθούν:

```
$ ./meta "I solemnly swear I am up to no good" "Magic glimmers brightly Magic creatures stand under the moonlight"
You can metamorphose the first sentence into the second sentence
I <-> Magic
solemnly <-> glimmers
swear <-> brightly
am <-> creatures
up <-> stand
to <-> under
no <-> the
good <-> moonlight
$ ./meta "I solemnly swear I am up to no good" "Magic glimmers brightly magic creatures stand under the moonlight"
You cannot metamorphose the first sentence into the second sentence
```



