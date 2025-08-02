# 🧠 Tic Tac Toe Bot (C++)

A fully functional terminal-based **Tic Tac Toe** game in C++ featuring a **bot opponent** with both **defensive and offensive logic**. The AI attempts to win proactively while also blocking the player when necessary. Built using simple condition checking and basic algorithms—no external libraries or machine learning used.

---

## 🎮 Features

- **Player vs Bot** mode  
- Bot logic includes:
  - Center-priority move
  - Win-detection
  - Block opponent's winning move
  - Random fallback strategy
- Clean turn-based interface in terminal
- Win/draw/tie condition checks
- Easy-to-read code and modular structure

---

## 🛠 How It Works

- The board is a 3x3 grid implemented using a 2D array.
- Each move is analyzed for potential win or loss situations.
- The bot first checks if it can win in the next move.
- If not, it checks if the player is about to win and blocks them.
- If nothing critical, it tries to take the center or a random free spot.

---

## 🚀 How to Run

### Compile:
```bash
g++ main.cpp logic.cpp board.cpp -o tictactoe
```
```bash
.\tictactoe
```
---

## 🧠 Future Improvements

- Add difficulty levels (Easy, Medium, Hard)  
- Implement Minimax algorithm for unbeatable AI  
- GUI using SFML or SDL for visual interface  

---

