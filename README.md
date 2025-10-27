# Flashcards Console App

A **cross-platform console flashcard application** written in C++.  
Designed for **learning and revising topics**, supporting multi-line flashcards, persistent storage, and easy navigation.

---

## 🔹 Features

### Version History
| Version | Notes |
|---------|-------|
| **v0.2 (Current)** | Refactored project structure into multiple files (Deck, Flashcard, Quiz, Storage, Utils). Easier to extend with new features like quiz modes, stats, groups, spaced repetition, and TUI. Maintains full cross-platform support. |
| **v0.1.x** | Initial features: Add/List/Quiz flashcards, multi-line support, persistent storage (`data/cards.txt`), Edit/Delete cards, improved Add Card workflow, quiz session stats, cross-platform screen clearing, numeric menu input. |

## 🔹 Project Structure

```bash
Flashcards/
├─ bin/           # compiled executable
├─ src/           # source code
│  ├─ main.cpp
│  ├─ Deck.cpp
│  ├─ Flashcard.cpp
│  ├─ Quiz.cpp
│  ├─ Storage.cpp
│  └─ Utils.cpp
├─ include/       # header files
│  ├─ Deck.hpp
│  ├─ Flashcard.hpp
│  ├─ Quiz.hpp
│  ├─ Storage.hpp
│  └─ Utils.hpp
├─ data/          # save files (tracked only with .gitkeep)
│  └─ .gitkeep
├─ .gitignore
└─ README.md

```

> `data/cards.txt` is automatically created when the app runs.  
> Do **not** commit this file — it is ignored in Git.

---

## 🔹 How to Run

### Linux

1. Compile:
```bash
g++ -std=c++17 -Iinclude src/*.cpp -o bin/app

```
2. Run:
```bash
./bin/app
```

### Windows (using MinGW)

1. Compile:
```bash
g++ -std=c++17 -Iinclude src/*.cpp -o bin/app.exe

```
2. Run:
```bash
bin\app.exe
```

---

## 🔹 How Save File Works
- File path: `data/cards.txt`
- Stores all flashcards in a simple line-by-line format.
- Multi-line flashcards are handled with an escape/unescape mechanism:
    - Each newline inside front/back is stored as `\n` in the file.
    - Loaded back into memory with original formatting intact.
- Example:
    > What is the capital\nof France?<br>
    > Paris
- **Do not edit manually unless you understand escape sequences,** or the program may misread flashcards.

---

## 🔹 Usage
1. Add flashcards
    - Choose menu option `1`
    - Enter question (front)
    - Enter answer (back)
    - If a duplicate front exists, you can choose to update the back
2. List flashcards
    - Choose menu option `2`
    - Displays all saved flashcards
    - Fromt the list, you can:
        - **Edit a card** -> choose card ID, update front/back
        - **Delete a card** -> choose card ID, confirm deletion
3. Quiz mode
    - Choose menu option `3`
    - Shows each question and waits for Enter to show answer
    - After seeing the answer, mark if you answered correctly
    - Move to next card with Enter
    - At the end, summary statistics are shown (total answered, correct, incorrect, percentage)
4. Quit
    - Choose menu option `4`
    - Saves all cards automatically

---

## 🔹 Development Notes
- Code is cross-platform: Linux, macOS, Windows
- `data/` folder is tracked using `.gitkeep`
- `cards.txt` is local, never tracked in Git
- Future improvements:
    - Search/filter cards
    - Shuffle quiz mode
    - Categories/tags for cards
    - Statistics and analytics
    - New methods of answering
    - CSV/JSON export of stats
    - Improved UI (TUI)
    - Spaced repetition algorithm

---

## 🔹 License
This project is MIT Licensed.