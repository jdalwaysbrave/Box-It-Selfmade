# Box-It Game (推箱子游戏)

A classic Sokoban-style puzzle game implemented in C with a graphical interface using Windows graphics library.

## 📖 Description

Box-It is a puzzle game where the player needs to push boxes to designated target locations within a limited time and number of moves. The game features:
- Classic Sokoban gameplay mechanics
- Time-based scoring system
- Move counter system
- Save/Load game functionality
- High score ranking system
- Multiple game states (start, playing, paused, success, failure)

## 🎮 Game Objective

Push all the wooden boxes to the target destinations marked on the map. Your score is calculated based on the remaining time and moves: **Score = Remaining Time × Remaining Moves**

## 🎯 Features

- **Start Game**: Begin a new game session
- **Resume Game**: Load a previously saved game
- **Pause/Resume**: Pause the game at any time and resume later
- **Save Progress**: Save your current game state
- **Ranking System**: Track top 5 high scores
- **Game Instructions**: Built-in help system explaining controls and scoring
- **Visual Interface**: Graphical representation of the game board with:
  - Player character (4 directional sprites)
  - Wooden boxes
  - Target destinations
  - Forest/wall obstacles
  - Background scenery

## 🕹️ Controls

### Keyboard Controls
- **Arrow Keys**: Move the player character
  - `↑` (Up Arrow): Move up
  - `↓` (Down Arrow): Move down
  - `←` (Left Arrow): Move left
  - `→` (Right Arrow): Move right

### Function Keys
- **F1**: Start new game
- **F2**: Load saved game
- **F3**: Quit game
- **F4**: Display rankings
- **F5**: Show game instructions
- **ESC**: Close modal windows/return to menu

### Mouse Controls
- Click on buttons to navigate menus and interact with game options

## 🏗️ Project Structure

```
Box-It-Selfmade/
├── begin.c           # Main menu and start page logic
├── pushbox.c         # Core game logic and mechanics
├── components.c      # UI components (buttons, links)
├── draw.c           # Drawing functions for all game elements
├── graphics.exe     # Compiled executable
├── include/         # Header files
│   ├── begin.h
│   ├── pushbox.h
│   ├── components.h
│   ├── draw.h
│   ├── graphics.h
│   ├── extgraph.h
│   ├── genlib.h
│   ├── simpio.h
│   ├── strlib.h
│   ├── random.h
│   └── exception.h
└── libgraphics/     # Graphics library source files
    ├── graphics.c
    ├── genlib.c
    ├── simpio.c
    ├── strlib.c
    ├── random.c
    └── exceptio.c
```

## 📋 Game Constants

- **Initial Moves**: 240 moves
- **Initial Time**: 120 seconds (120,000 milliseconds)
- **Target Boxes**: 4 boxes need to be placed on target destinations
- **Ranking Spots**: Top 5 scores are saved

## 🎲 Game Elements

### Map Elements (Internal Representation)
- `0`: Empty space
- `1`: Wall (forest/obstacle)
- `2`: Player facing up
- `3`: Target destination
- `4`: Player facing left
- `5`: Player facing right
- `6`: Player facing down
- `7`: Wooden box
- `8`: Box placed on target destination

## 💾 File System

The game uses two text files for persistence:
- **savefile.txt**: Stores the current game state (map, time, moves)
- **rankfile.txt**: Stores the top 5 high scores

## 🖥️ Technical Details

### Platform
- **OS**: Windows (uses Windows API for graphics)
- **Language**: C
- **Graphics**: Custom graphics library (libgraphics)

### Key Components

1. **begin.c**: Handles the start menu, game initialization, and menu navigation
2. **pushbox.c**: Contains the main game loop, player movement, collision detection, and game state management
3. **components.c**: Implements UI elements like buttons and linked list management for UI components
4. **draw.c**: Rendering functions for all visual elements including characters, boxes, walls, backgrounds, and success/failure screens

### Graphics Functions
- Custom drawing primitives (boxes, triangles, circles)
- Color management system
- Filled region support
- Text rendering with custom fonts

## 🚀 Building and Running

### Prerequisites
- Windows operating system
- C compiler (MinGW or Visual Studio)
- Graphics library (libgraphics included)

### Compilation
The project can be compiled using a C compiler that supports Windows API:
```bash
gcc -o graphics.exe begin.c pushbox.c components.c draw.c libgraphics/*.c -I./include -lgdi32 -lwinmm -lole32
```

### Running
Simply execute the compiled `graphics.exe` file:
```bash
./graphics.exe
```

## 🎨 Game Screens

1. **Start Menu**: Main entry point with options to start, resume, quit, view rankings, or see help
2. **Game Screen**: Active gameplay with map display, player, boxes, and status indicators (time/moves)
3. **Pause Menu**: Options to save, resume, or quit to main menu
4. **Success Screen**: Displayed when all boxes are placed correctly, shows final score
5. **Failure Screen**: Shown when time runs out or moves are exhausted
6. **Rankings**: Displays top 5 high scores
7. **Help Screen**: Game instructions and controls

## 📊 Scoring System

Your final score is calculated as:
```
Score = Remaining Time (in seconds) × Remaining Moves
```

The higher the score, the better! Try to complete the puzzle as quickly and efficiently as possible.

## 🎓 Game Rules

1. Use arrow keys to move the player character
2. Push boxes by walking into them (you cannot pull boxes)
3. You can only push one box at a time
4. Boxes can only be pushed to empty spaces or target destinations
5. Complete the level by placing all boxes on target destinations
6. Watch your time and move count - running out of either results in failure
7. Plan your moves carefully as boxes can get stuck against walls

## 🏆 Tips

- Plan your route before moving
- Try to minimize moves by thinking ahead
- Keep an eye on the timer
- Boxes cannot be pulled, only pushed
- Some positions can trap boxes permanently, requiring a restart
- Use the save feature to preserve progress on difficult puzzles

## 👥 Credits

This is a self-made implementation of the classic Sokoban puzzle game.

## 📝 License

This project is available for educational purposes.

---

**Enjoy playing Box-It! Push those boxes and beat the high scores! 🎮📦**
