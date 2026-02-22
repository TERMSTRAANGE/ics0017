# ICS0017 Project
## Description
### Simple, CLI-only implementation of blackjack in C++
## Features
- Core game mechanics
- Basic funds management
- User data storage through save files
## Repository structure
```md
.
├── docs       # Documentation
├── src        # Source files
├── .gitignore
└── README.md
```
## How to build and run
```bash
cmake -B build
cmake --build build
```

Executable will be found in the `build/` subdirectory under the name of `ics0017`(or `ics0017.exe` on Windows environments)

## TODO
- [ ] Funds
- [ ] Dynamic Memory
- [ ] Saving
- [ ] Operator Overloading
    - [ ] Move Operator
    - [ ] *ostream* Operator