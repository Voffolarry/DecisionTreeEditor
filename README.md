# Larry - Visual Decision Tree Editor

![C++](https://img.shields.io/badge/C++-17/20-blue.svg)
![SDL3](https://img.shields.io/badge/SDL3-3.0.0-green.svg)
![Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20Linux-lightgrey.svg)
![License](https://img.shields.io/badge/License-MIT-yellow.svg)

**Larry** is a modern, interactive visual editor for creating and managing decision trees. Built with C++ and SDL3, it provides an intuitive drag-and-drop interface with smooth animations, customizable node types, and a polished user experience.

![Larry Screenshot](screenshot.png)

## ✨ Features

### 🎨 Visual Editor
- **Drag-and-Drop Interface** - Intuitive node manipulation with mouse
- **Smooth Animations** - Pop-in effects on creation, hover scaling, smooth transitions
- **Multiple Node Types** - Start, Action, Condition, and End nodes with distinct visual styles
- **Custom Shapes** - Circle, Rectangle, Diamond, and Capsule primitives
- **Bezier Connections** - Elegant curved connections between nodes with labels

### 🎯 Node Management
- **Click to Select** - Single-click selection with visual feedback
- **Drag Entire Subtrees** - Move a node and all its children together
- **Right-Click to Add** - Quick child node creation
- **Delete Key Support** - Remove nodes with keyboard shortcut
- **Labeled Connections** - "Yes"/"No" labels for conditional branches

### 🖥️ User Interface
- **Menu Bar** - File, Edit, View, and Help menus
- **Tab System** - Multiple document interface with drag-to-reorder tabs
- **Sidebar Palette** - Quick access to node creation tools
- **Inspector Panel** - Edit node properties (label, type, style)
- **Text Input Widget** - Direct label editing with focus management
- **Responsive Layout** - Panels adjust to window size

### ⚡ Performance
- **Incremental Compilation** - Fast rebuild times
- **Efficient Rendering** - Hardware-accelerated SDL3 rendering
- **Smooth 60 FPS** - Consistent frame rate with animations

## 🏗️ Architecture

### Project Structure

```
DecisionTreeEditor/
├── Build/                      # Compiled binaries and object files
│   ├── Objects/                # Intermediate .o files
│   └── Larry.exe               # Final executable
│
├── Sources/                    # Source code
│   ├── Core/                   # Core engine components
│   │   ├── Window.h/cpp        # SDL3 window management
│   │   └── Input.h/cpp         # Keyboard & mouse input handling
│   │
│   ├── Graphics/               # Rendering system
│   │   ├── Renderer.h/cpp      # Drawing primitives and shapes
│   │   └── SimpleFont.h        # Embedded 8x8 bitmap font
│   │
│   ├── Data/                   # Data structures
│   │   └── TreeNode.h          # Node and connection definitions
│   │
│   ├── Editor/                 # Editor logic
│   │   ├── Editor.h/cpp        # Core editing (selection, dragging, hit-testing)
│   │   └── Layout.h/cpp        # UI layout and widget management
│   │
│   ├── UI/                     # UI widget system
│   │   ├── Widget.h            # Base widget class
│   │   ├── Panel.h             # Container widget
│   │   ├── Button.h            # Clickable buttons
│   │   ├── TabBar.h            # Multi-tab interface
│   │   ├── MenuBar.h           # Top menu bar
│   │   ├── TextInput.h         # Text editing widget
│   │   └── Label.h             # Static text display
│   │
│   └── Main.cpp                # Application entry point
│
├── Resources/                  # Configuration and assets
│   └── app.config              # Application settings
│
├── Tools/Commands/             # Build scripts
│   ├── Build.bat               # Windows build script
│   └── Build.sh                # Linux build script
│
├── larry.bat                   # Windows build wrapper
├── larry.sh                    # Linux build wrapper
└── README.md                   # This file
```

### Component Architecture

```
┌─────────────────────────────────────────────────────────────┐
│                        Main.cpp                              │
│                    (Application Loop)                        │
└────────────┬────────────────────────────────────────────────┘
             │
             ├──► Core::Window ──► SDL3 Window & Renderer
             │
             ├──► Core::Input ──► Keyboard & Mouse State
             │
             ├──► Editor::Layout ──┬──► UI::MenuBar
             │                     ├──► UI::TabBar
             │                     ├──► UI::Panel (Sidebar)
             │                     └──► UI::Panel (Inspector)
             │                           └──► UI::TextInput
             │
             └──► Editor::Editor ──┬──► Data::TreeNode (Root)
                                   ├──► Selection & Dragging
                                   ├──► Hit Testing
                                   └──► Graphics::Renderer
                                         └──► Drawing Primitives
```

### Data Model

#### TreeNode Structure
```cpp
struct TreeNode {
    std::string Label;              // Node display text
    NodeType Type;                  // Start, Action, Condition, End
    ShapeType Shape;                // Circle, Rectangle, Diamond, Capsule
    uint8_t R, G, B;               // Node color
    float X, Y;                     // Position
    float Scale, TargetScale;       // Animation state
    std::vector<Connection> Connections;  // Child nodes with labels
    bool IsLeaf;
};

struct Connection {
    std::string Label;              // "Yes", "No", or custom
    TreeNode* Target;               // Child node
};
```

#### Node Types
- **Start** (Green Circle) - Entry point of the decision tree
- **Action** (Blue Rectangle) - Executable action or task
- **Condition** (Yellow Diamond) - Decision point with Yes/No branches
- **End** (Red Capsule) - Terminal node

### Rendering Pipeline

1. **Clear Canvas** - Dark background (30, 30, 30)
2. **Draw Tree** - Recursive depth-first traversal
   - Draw connections (Bezier curves)
   - Draw connection labels
   - Draw nodes (filled shapes with outlines)
   - Draw node labels (embedded font)
3. **Draw UI** - Layered rendering
   - Menu bar (top)
   - Tab bar
   - Sidebar panels
   - Inspector panel
   - Widgets (buttons, text inputs)
4. **Present** - SDL3 buffer swap

### Input Handling

```
Frame Start
    ↓
Core::Input::Update()  ← Snapshot previous state
    ↓
SDL_PollEvent()        ← Process system events
    ↓
Layout::Update()       ← UI widgets (returns handled flag)
    ↓
Editor::Update()       ← Canvas editing (if not handled by UI)
    ↓
Render
```

### Animation System

Nodes use lerp-based animation:
```cpp
// In DrawNodeRecursive()
float lerpSpeed = 0.1f;
node->Scale += (node->TargetScale - node->Scale) * lerpSpeed;

// Scale values:
// 0.0f  - Hidden (pop-in start)
// 1.0f  - Normal size
// 1.2f  - Hovered/selected
```

## 🚀 Getting Started

### Prerequisites

- **C++ Compiler**: Clang++ (recommended) or GCC/G++
- **SDL3**: Graphics library (version 3.0.0+)
- **System**: Windows (MSYS2) or Linux

### Installation

#### Windows (MSYS2)

1. Install MSYS2 from https://www.msys2.org/
2. Open MSYS2 UCRT64 terminal
3. Install dependencies:
```bash
pacman -S mingw-w64-ucrt-x86_64-clang mingw-w64-ucrt-x86_64-SDL3
```

#### Linux (Ubuntu/Debian)

```bash
sudo apt install clang libsdl3-dev
```

### Building

#### Windows
```cmd
larry.bat build
larry.bat run
```

#### Linux
```bash
chmod +x larry.sh
./larry.sh build
./larry.sh run
```

### Build Options

```bash
# Clean build
./larry.sh clean

# Build only (no run)
./larry.sh build

# Run without rebuilding
./larry.sh run
```

## 🎮 Usage

### Mouse Controls

| Action | Description |
|--------|-------------|
| **Left Click** | Select node or UI element |
| **Left Drag** | Move selected node and entire subtree |
| **Right Click** | Add child node to hovered node |
| **Hover** | Highlight node with scaling animation |

### Keyboard Controls

| Key | Description |
|-----|-------------|
| **Delete** | Delete selected node |
| **Backspace** | Delete selected node (or remove characters in text input) |
| **Type** | Edit node label when text input is focused |

### UI Elements

- **Sidebar Buttons** - Click to create new nodes (Start, Action, Condition, End)
- **Inspector Panel** - Edit selected node label via text input
- **Delete Button** - Remove selected node
- **Tab Bar** - Click to switch tabs, drag to reorder, click `+` to add new tab
- **Menu Bar** - Access File, Edit, View, and Help menus

### Workflow Example

1. **Create Root Node** - Click "Add Start" in sidebar
2. **Add Decision** - Right-click on Start node → creates Action node
3. **Change Type** - Select node, use inspector to modify
4. **Edit Label** - Click text input in inspector, type new name
5. **Move Subtree** - Drag node to reposition it and all children
6. **Delete Node** - Select node, press Delete key or click Delete button

## 🔧 Configuration

### Application Settings (`Resources/app.config`)

```ini
windowTitle=Larry - Decision Tree Editor
windowWidth=1280
windowHeight=720
fullscreen=false
resizable=true
vsync=true
targetFPS=60
```

### Demo Settings (`Resources/demos.config`)

```ini
[decisiontree]
enabled=true
name=Decision Tree Editor
description=Visual editor for creating and managing decision trees
```

## 🛠️ Development

### Adding a New Node Type

1. **Update `NodeType` enum** in `Data/TreeNode.h`
2. **Add color/shape mapping** in `TreeNode` constructor
3. **Create sidebar button** in `Editor/Layout.cpp`
4. **Update rendering** in `Graphics/Renderer.cpp` if needed

### Creating a New UI Widget

1. **Inherit from `UI::Widget`** in `Sources/UI/`
2. **Implement `Update()` and `Draw()` methods**
3. **Return `true` from `Update()` if input was handled**
4. **Add to `Layout` in `Editor/Layout.cpp`**

### Build System Details

The build system (`larry.bat`/`larry.sh`) performs:
- **Incremental compilation** - Only recompiles changed files
- **Dependency detection** - Automatically finds all `.cpp` files
- **SDL3 linking** - Handles platform-specific library paths
- **Object file management** - Stores `.o` files in `Build/Objects/`

## 📋 Roadmap

### Completed ✅
- [x] Core visual editor with node manipulation
- [x] Multiple node types and shapes
- [x] Connection labels (Yes/No)
- [x] Animations (pop-in, hover scaling)
- [x] Text input for label editing
- [x] Tab system with drag-and-drop
- [x] Menu bar
- [x] Subtree dragging
- [x] Inspector panel

### Planned 🚧
- [ ] File operations (Save/Load JSON)
- [ ] Undo/Redo system
- [ ] Node style customization UI (color picker, shape selector)
- [ ] Export to various formats (PNG, SVG, Code generation)
- [ ] Zoom and pan canvas
- [ ] Search and filter nodes
- [ ] Keyboard shortcuts (Ctrl+C, Ctrl+V, etc.)
- [ ] Themes and color schemes
- [ ] Multi-selection
- [ ] Clipboard operations
- [ ] Auto-layout algorithms

## 🐛 Known Issues

- Large trees may require manual repositioning
- No file save/load yet (in-memory only)
- Tab close button not implemented

## 📄 License

This project is under the MIT License. See the LICENSE file for details.

## 🤝 Contributing

Contributions are welcome! To contribute:

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/amazing-feature`)
3. Commit your changes (`git commit -m 'Add amazing feature'`)
4. Push to the branch (`git push origin feature/amazing-feature`)
5. Open a Pull Request

### Code Style
- Use C++17/20 features
- Follow existing naming conventions (PascalCase for classes, camelCase for variables)
- Keep functions focused and under 50 lines when possible
- Comment complex algorithms

## 📞 Support

For questions, issues, or feature requests:
- Open an issue on GitHub
- Check existing issues for solutions
- Provide detailed reproduction steps for bugs

## 🙏 Acknowledgments

- **SDL3** - Simple DirectMedia Layer for cross-platform graphics
- **Nature of Code** - Inspiration for visual design patterns
- Built with ❤️ for visual thinkers and decision makers

---

**Larry** - *Visual Decision Tree Editor*  
Version 1.0.0 | 2026
