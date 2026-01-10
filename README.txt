Arena Matchmaker (C++)

A fast matchmaking and leaderboard system built using a Binary Search Tree.

This program manages players in a game arena using their rating as the key. It supports joining, leaving, searching, ranking, matchmaking, and many other operations in real time.

--------------------------------------------------

FEATURES

- Add and remove players
- Search player by rating
- Damage and heal players
- Find nearest opponent (matchmaking)
- Get next and previous rated players
- Print players in a rating range
- Find rank and k-th smallest player
- Calculate duel distance between two players
- Show full system statistics (height, leaves, min, max, total players)

All operations follow the exact rules given in the exam problem statement.

--------------------------------------------------

DATA STRUCTURE USED

- Pointer-based Binary Search Tree (BST)
- Ordered only by rating
- No STL ordered containers (map, set, etc.)

--------------------------------------------------

FILE NAME

Recommended:

arenaMatchmaker.cpp

--------------------------------------------------

HOW TO COMPILE AND RUN

Compile:

g++ arenaMatchmaker.cpp -o arena

Run:

./arena

Then enter the number of commands followed by the commands.

--------------------------------------------------

EXAMPLE INPUT

3
JOIN 10 Alex 100
STATUS 10
STATS

--------------------------------------------------

EXAMPLE OUTPUT

JOINED
10 Alex 100
PLAYERS 1
MIN 10
MAX 10
HEIGHT 0
LEAVES 1

--------------------------------------------------

NOTES

- Ratings must be unique
- Output is case-sensitive
- Works efficiently for large input sizes
- Fully matches the provided exam specification

--------------------------------------------------

