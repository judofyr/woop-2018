# Woop

Woop is a programming language and environment that is almost entirely written in itself and is easy to bootstrap.
You only need an interpreter for the virtual machine (which can be done in very few lines of C), and by loading hand-written bytecode you get a fully functional C-style language with an interactive shell.

More specifically Woop contains:

- **WoopVM:** An untyped, stack-based virtual machine with an interpreter written in C.
  The VM has enough features (conditionals, blocks) that it's doable to write programs in bytecode by hand.

- **Bytecode assembler/linker:** A DSL for writing bytecode for the WoopVM.

- **Type system:** A basic, C-style, type system that handles numbers, pointers and structs (with correct alignment and field offsets).
  This is written as a library in bytecode.

- **WoopLang:** A typed, C-style language that has higher-level features such as structred control flow, struct fields and functions.
  WoopLang has a stack-based binary representation, and there's a compiler (written in bytecode) which converts this representation into bytecode.

- **Parser:** Parses a file/string into the binary representation of WoopLang.

- **Shell:** Interactive shell that let's you write Woop programs on the command-line.

## Status

Woop is currently under development and will be published once there is a working prototype.

## Running

You need a C compiler which supports C99.

Run the tests:

    $ make test

## Credits

In spirit, Woop is heavily inspired by the Forth language/environment.
Forth demonstrated that it is possible to get reasonable high-level, interactive environment with few lines of code by defining a simple, expressive language at the bottom.
Woop currently has a higher (implementation) complexity than Forth, but in exchange we get "normal" programming constructs such as functions, variables and blocks.

In implementation, Woop is a result from many years of experimenting with languages, intermediate representations and virtual machines.
We're forever grateful to the programming and computer science community which keeps on publishing fascinating ideas.

## License

Woop is is available under the [Blue Oak Model License 1.0.0](LICENSE.md).
