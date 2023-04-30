# Proiect PA - Crazy House Chess Engine

## Compile Instructions

```console
maria@spectrum:~/proiect-pa-2023-exploding-pengwins.git$ cd src/
```

### Build

```console
maria@spectrum:~/proiect-pa-2023-exploding-pengwins.git/src$ make build
```

### Run

```console
maria@spectrum:~/proiect-pa-2023-exploding-pengwins.git/src$ make run
```

### Clean

```console
maria@spectrum:~/proiect-pa-2023-exploding-pengwins.git/src$ make clean
```

## Structure

```console
.
├── CONTRIBUTING.md
├── cs
│   └── check_cpp.py
├── README.md
└── src
    ├── Bot.cpp
    ├── Bot.h
    ├── Main.cpp
    ├── Makefile
    ├── Move.cpp
    ├── Move.h
    ├── MoveNode.cpp
    ├── MoveNode.h
    ├── Piece.h
    ├── PlaySide.h
    └── xboard.debug
```

* `Bot.cpp`, `Bot.h`:

   &rarr; the code necessary for configuring the bot, such as the `checkRepeatedConfigs()` method which gets whether the current configuration repetead itself 3 times.

* `Main.cpp`:

   &rarr; the code for the xboard communication

* `Move.cpp`, `Move.h`:

   &rarr; the skel which was used for actions such as dropping pieces in (Crazy House Chess) and promotions.

* `MoveNode.cpp`, `MoveNode.h`:

   &rarr; special class, a wraper over `Move` with auxiliary functionalities

   &rarr; the code that generates all possible moves for all pieces in such a manner that the king doesn't get instantly attacked (eg `knightMoves()`, `bishopMoves()`)

   &rarr; the methods used for checking whether a piece attacks the king, or is in a special case (eg `checkRookAttack()`, `checkSpecialCases()`)

   &rarr; the methods that deal with Crazy House rules, such as `switchSide()`, which gets all captured pieces, changes their color and transforms the ones that were promoted, back into pawns

## Algorithmic Approach



## Bibliography

[Chess Programming](https://www.chessprogramming.org/Main_Page#Basics)

## Members and Their Work

Alexandru Mihai _Zeus, the mastermind behind the project_

   &rarr; debugging
   
   &rarr; refactoring
   
   &rarr; en-passant
   
   &rarr; castling
   
   &rarr; corner chess cases

Delia Constantinescu, _protector from the wrath of the mastermind_

   &rarr; debugging
   
   &rarr; record all possible moves for pawns, knight, king

Ecaterina Mincă, _the code breaker, tested the bot like hellllll_

   &rarr; debugging
   
   &rarr; record all possible moves for pawns, knight, king

Maria Sfîrăială, _the git girl that took a vacation_

   &rarr; README
   
   &rarr; coding style
   
   &rarr; place Crazy House pieces
   
   &rarr; generate next move (integrate Cati, Delia, Maria work)   
