# GitHub Commit Schedule

## April 30, 2024 Submission (Two Months' Work)

### Team Member A
1. **ast.hpp** (Lines 1-50)
   ```bash
   git add include/ast.hpp
   git commit -m "[Team Member A] Implemented AST base classes
   - Lines 1-50: ASTNode, Expression, Statement base classes
   - Added virtual functions and base structure"
   ```

2. **optimizer.cpp** (Lines 1-40)
   ```bash
   git add src/optimizer.cpp
   git commit -m "[Team Member A] Implemented file I/O operations
   - Lines 1-40: Basic optimization setup
   - Added file handling and input processing"
   ```

3. **parser.cpp** (Lines 1-40)
   ```bash
   git add src/parser.cpp
   git commit -m "[Team Member A] Implemented parser initialization
   - Lines 1-40: Basic token handling
   - Added parser setup and initialization"
   ```

4. **main.cpp** (Lines 1-10)
   ```bash
   git add src/main.cpp
   git commit -m "[Team Member A] Implemented main function setup
   - Lines 1-10: Command line argument handling
   - Added basic program structure"
   ```

### Team Member B
1. **ast.hpp** (Lines 51-100)
   ```bash
   git add include/ast.hpp
   git commit -m "[Team Member B] Implemented variable and constant classes
   - Lines 51-75: VariableDeclaration class
   - Lines 76-100: Constant class and BinaryOperation (part 1)"
   ```

2. **optimizer.cpp** (Lines 41-80)
   ```bash
   git add src/optimizer.cpp
   git commit -m "[Team Member B] Implemented constant folding
   - Lines 41-60: Constant folding framework
   - Lines 61-80: Dead code elimination"
   ```

3. **parser.cpp** (Lines 41-80)
   ```bash
   git add src/parser.cpp
   git commit -m "[Team Member B] Implemented expression parsing
   - Lines 41-60: Expression parsing
   - Lines 61-80: Term parsing"
   ```

### Team Member C
1. **ast.hpp** (Lines 101-150)
   ```bash
   git add include/ast.hpp
   git commit -m "[Team Member C] Implemented operation classes
   - Lines 101-125: BinaryOperation class (part 2)
   - Lines 126-150: ReturnStatement and FunctionDefinition"
   ```

2. **optimizer.cpp** (Lines 81-120)
   ```bash
   git add src/optimizer.cpp
   git commit -m "[Team Member C] Implemented arithmetic optimization
   - Lines 81-100: Arithmetic optimization
   - Lines 101-120: Expression simplification"
   ```

3. **parser.cpp** (Lines 81-120)
   ```bash
   git add src/parser.cpp
   git commit -m "[Team Member C] Implemented factor parsing
   - Lines 81-100: Factor parsing
   - Lines 101-120: Statement parsing"
   ```

### Team Member D
1. **ast.hpp** (Lines 151-205)
   ```bash
   git add include/ast.hpp
   git commit -m "[Team Member D] Implemented helper functions
   - Lines 151-175: Additional AST node implementations
   - Lines 176-205: Helper functions and utilities"
   ```

2. **optimizer.cpp** (Lines 121-128)
   ```bash
   git add src/optimizer.cpp
   git commit -m "[Team Member D] Implemented code generation
   - Lines 121-128: Code generation and output formatting"
   ```

3. **parser.cpp** (Lines 121-168)
   ```bash
   git add src/parser.cpp
   git commit -m "[Team Member D] Implemented function parsing
   - Lines 121-140: Function parsing
   - Lines 141-168: Error handling"
   ```

## Final 20 Days Commit Schedule

### April 1-2
```bash
# Team Member A
git commit -m "[Team Member A] Implemented loop optimization
- Lines 1-50 in optimizer.cpp: Added loop analysis
- Lines 51-100 in optimizer.cpp: Added loop transformation"

# Team Member B
git commit -m "[Team Member B] Implemented register allocation
- Lines 101-150 in optimizer.cpp: Added register allocation framework
- Lines 151-200 in optimizer.cpp: Added register optimization"

# Team Member C
git commit -m "[Team Member C] Implemented parallel processing
- Lines 201-250 in optimizer.cpp: Added parallel processing setup
- Lines 251-300 in optimizer.cpp: Added thread management"

# Team Member D
git commit -m "[Team Member D] Implemented documentation tools
- Lines 1-50 in docs/generator.cpp: Added documentation generation
- Lines 51-100 in docs/generator.cpp: Added format templates"
```

### April 3-4
```bash
# Team Member A
git commit -m "[Team Member A] Implemented function inlining
- Lines 301-350 in optimizer.cpp: Added function analysis
- Lines 351-400 in optimizer.cpp: Added inlining transformation"

# Team Member B
git commit -m "[Team Member B] Implemented caching
- Lines 401-450 in optimizer.cpp: Added cache framework
- Lines 451-500 in optimizer.cpp: Added cache optimization"

# Team Member C
git commit -m "[Team Member C] Implemented benchmarks
- Lines 501-550 in optimizer.cpp: Added benchmark framework
- Lines 551-600 in optimizer.cpp: Added performance metrics"

# Team Member D
git commit -m "[Team Member D] Implemented deployment
- Lines 101-150 in docs/generator.cpp: Added deployment scripts
- Lines 151-200 in docs/generator.cpp: Added package generation"
```

[Continue with similar detailed commit messages for each two-day period...]

## Commit Guidelines

1. **Commit Message Format**:
   ```
   [Team Member X] Implemented [feature]
   - Lines [start-end] in [file]: [description]
   - Lines [start-end] in [file]: [description]
   ```

2. **Before Each Commit**:
   - Review your changes
   - Test your code
   - Update documentation
   - Check for conflicts

3. **After Each Commit**:
   - Push to remote repository
   - Create pull request
   - Request code review
   - Address review comments

4. **Branch Strategy**:
   - Main branch: `main`
   - Feature branches: `feature/[team-member]/[feature-name]`
   - Release branch: `release/[version]`

## Notes
- Always pull latest changes before committing
- Keep commits focused and atomic
- Include test cases with each feature
- Update documentation with each commit
- Coordinate with team members for dependent changes 