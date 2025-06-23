Compiler Pipeline Project
========================

This is a terminal-based compiler for a small language (variables, arithmetic, assignment, loops, conditionals) with a full pipeline:

- Lexical Analysis (tokens.txt)
- Syntax Analysis (parse_tree.txt)
- Semantic Analysis (symbol_table.txt)
- Intermediate Code Generation (tac.txt)
- Code Optimization (optimized_output.txt)

Each phase outputs its result to a .txt file for debugging and inspection.

Usage:
------
python3 compiler.py input_code.txt

Sample input program is provided in input_code.txt.

Requirements:
-------------
- Python 3.x

Files:
------
- compiler.py: Main driver
- lexer.py: Lexical analysis
- parser_module.py: Syntax analysis
- semantic_analyzer.py: Semantic analysis
- tac_generator.py: Three-address code generation
- optimizer.py: Code optimization
- utils.py: Helper functions
- input_code.txt: Sample input program 