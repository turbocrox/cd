# First Commit Guide for Team Members

## Initial Setup

1. **Clone the Repository**
   ```bash
   git clone <repository-url>
   cd <repository-name>
   ```

2. **Create Your Feature Branch**
   ```bash
   # Replace [your-name] with your actual name (A, B, C, or D)
   git checkout -b feature/[your-name]/initial-setup
   ```

3. **Set Up Remote Tracking** (If you get upstream branch error)
   ```bash
   # If you get the error: "fatal: The current branch has no upstream branch"
   git push --set-upstream origin feature/[your-name]/initial-setup
   
   # Or use the shorter version
   git push -u origin feature/[your-name]/initial-setup
   ```

## Making Your First Commit

### For Team Member A
1. **Edit ast.hpp** (Lines 1-50)
   ```bash
   # Open and edit the file
   nano include/ast.hpp
   # or use your preferred editor
   ```

2. **Stage Your Changes**
   ```bash
   git add include/ast.hpp
   ```

3. **Commit Your Changes**
   ```bash
   git commit -m "[Team Member A] Implemented AST base classes
   - Lines 1-50: ASTNode, Expression, Statement base classes
   - Added virtual functions and base structure"
   ```

### For Team Member B
1. **Edit ast.hpp** (Lines 51-100)
   ```bash
   # Open and edit the file
   nano include/ast.hpp
   ```

2. **Stage Your Changes**
   ```bash
   git add include/ast.hpp
   ```

3. **Commit Your Changes**
   ```bash
   git commit -m "[Team Member B] Implemented variable and constant classes
   - Lines 51-75: VariableDeclaration class
   - Lines 76-100: Constant class and BinaryOperation (part 1)"
   ```

### For Team Member C
1. **Edit ast.hpp** (Lines 101-150)
   ```bash
   # Open and edit the file
   nano include/ast.hpp
   ```

2. **Stage Your Changes**
   ```bash
   git add include/ast.hpp
   ```

3. **Commit Your Changes**
   ```bash
   git commit -m "[Team Member C] Implemented operation classes
   - Lines 101-125: BinaryOperation class (part 2)
   - Lines 126-150: ReturnStatement and FunctionDefinition"
   ```

### For Team Member D
1. **Edit ast.hpp** (Lines 151-205)
   ```bash
   # Open and edit the file
   nano include/ast.hpp
   ```

2. **Stage Your Changes**
   ```bash
   git add include/ast.hpp
   ```

3. **Commit Your Changes**
   ```bash
   git commit -m "[Team Member D] Implemented helper functions
   - Lines 151-175: Additional AST node implementations
   - Lines 176-205: Helper functions and utilities"
   ```

## Pushing Your Changes

1. **Push Your Branch**
   ```bash
   # First time push (if you haven't set upstream)
   git push -u origin feature/[your-name]/initial-setup
   
   # Subsequent pushes
   git push
   ```

2. **Create Pull Request**
   - Go to GitHub repository
   - Click "Compare & pull request"
   - Add description of your changes
   - Request review from team members

## Common Git Errors and Solutions

1. **No Upstream Branch Error**
   ```bash
   # Error: "fatal: The current branch has no upstream branch"
   
   # Solution 1: Set upstream while pushing
   git push -u origin feature/[your-name]/initial-setup
   
   # Solution 2: Set upstream separately
   git branch --set-upstream-to=origin/feature/[your-name]/initial-setup
   ```

2. **Merge Conflicts**
   ```bash
   # If you get merge conflicts
   git status  # See conflicting files
   # Edit files to resolve conflicts
   git add .   # Add resolved files
   git commit  # Complete the merge
   ```

3. **Wrong Branch**
   ```bash
   # If you committed to wrong branch
   git checkout correct-branch
   git cherry-pick <commit-hash>
   ```

4. **Undo Last Commit**
   ```bash
   # If you need to undo last commit
   git reset --soft HEAD~1
   ```

## Important Notes

1. **Before Starting**
   - Make sure you have Git installed
   - Configure your Git identity:
     ```bash
     git config --global user.name "Your Name"
     git config --global user.email "your.email@example.com"
     ```
   - Set up automatic upstream tracking (optional):
     ```bash
     git config --global push.autoSetupRemote true
     ```

2. **While Working**
   - Keep your branch updated:
     ```bash
     git checkout main
     git pull
     git checkout feature/[your-name]/initial-setup
     git merge main
     ```
   - Resolve any conflicts if they occur

3. **Before Committing**
   - Review your changes:
     ```bash
     git diff
     ```
   - Make sure you're committing the right files:
     ```bash
     git status
     ```

4. **After Committing**
   - Test your changes
   - Update documentation
   - Create pull request
   - Wait for review

## Need Help?
- Check the commit schedule in `GITHUB_COMMIT_SCHEDULE.md`
- Review the project documentation
- Ask team members for assistance
- Check Git documentation 