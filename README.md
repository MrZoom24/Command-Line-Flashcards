# Flashcards Console App

A **cross-platform console flashcard application** written in C++.  
Designed for **learning and revising topics**, supporting multi-line flashcards, persistent storage, and easy navigation.

---

## 🔹 Features

### Version History
**v0.1.2 (Current)**
- Improved input experience

**v0.1.1**
- Improved **Add Card** workflow:
    - Can add multiple cards in one session
    - Added `:q` to exit card input
- Fixed input buffer bug when entering menu options

**v0.1**
- Add / List / Quiz flashcards
- Basic input handling
- Numeric menu selection
- Cross-platform screen clearing (`cls` for Windows, `clear` for Linux/macOS)
- Persistent storage in `data/cards.txt` (saved automatically)
- Supports **multi-line flashcards** using escape/unescape mechanism
- Keeps quiz question and answer together for better readability
- `.gitignore` configured to ignore local save file

---

## 🔹 Project Structure

```bash
Flashcards/
├─ bin/ # compiled executable
├─ src/ # source code
│ └─ main.cpp
├─ data/ # save files (tracked only with .gitkeep)
│ └─ .gitkeep
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
g++ -o bin/app src/main.cpp
```
2. Run:
```bash
./bin/app
```

### Windows (using MinGW)

1. Compile:
```bash
g++ -o bin/app.exe src/main.cpp
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
3. Quiz mode
    - Choose menu option `3`
    - Shows each question and waits for Enter to show answer
    - Move to next card with Enter
4. Quit
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
    - Statistics
    - New methods of answering
    - CSV/JSON export of stats
    - Improved UI
    - Editing/Deleting
    - Spaced repetition algorithm

---

## 🔹 License
This project is MIT Licensed.