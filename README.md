# Assembler Lexer

This repository provides a basic lexical analyzer (lexer) for the Assembler programming language.

## Overview

The lexer is designed to process Assembler source code and produce a sequence of tokens representing individual syntactic elements of the language. Each token consists of a lexeme and its type.

## Features

- Recognizes different classes of lexemes:
    - Decimal, floating-point, and hexadecimal numbers
    - String and character constants
    - Preprocessor directives
    - Comments
    - Reserved words
    - Operators
    - Separators
    - Identifiers
- Uses regular expressions for lexeme recognition.
