# Woop

Woop is a programming language and environment that is almost entirely written
in itself and is easy to bootstrap. You only need an interpreter for the virtual
machine (which can be done in ~150 lines of C), and by loading hand-written
bytecode you get a fully functional C-style language with an interactive shell.

More specifically Woop contains:

- WoopVM (`vm.c`): An untyped, register-based virtual machine with an
  interpreter written in C. We also provide C macros in order to write bytecode
  in text format. Bytecode is written in files named `something.vm.c` and they
  should not be considered "C files" (have a look for yourself).

- Type system (`type.vm.c`): A basic, C-style, type system that handles numbers,
  pointers and structs (with correct alignment and field offsets).

- WoopLang: A typed, C-style language that has higher-level features such as
  structred control flow, struct fields and functions. It has a stack-based
  binary representation and once again we provide C macros (`cmd.c`) in order to
  write programs without having a parser.

- Compiler (`compiler.vm.c`): Compiles Woop programs (in their binary
  representation) into WoopVM bytecode, making it possible to run Woop programs
  through the WoopVM interpreter.

- Parser (`parser.w.c`): Parses a file/string into the binary representation of
  Woop, making it possible to write Woop programs without using C macros.

- Shell (`shell.w`): Interactive shell that let's you write Woop programs on the
  command-line.

## Status

Woop is currently under development and will be published once there is a
working prototype.

## Running

You need a C compiler which supports C99.

Build the `woop` binary:

    $ make

Run:

    $ ./woop PROGRAM

Run the shell:

    $ ./woop src/shell.w

See the [`examples/` directory](examples) for more examples.

## Credits

In spirit, Woop is heavily inspired by the Forth language/environment. Forth
demonstrated that it is possible to get reasonable high-level, interactive
environment with few lines of code by defining a simple, expressive language at
the bottom. Woop currently has a higher (implementation) complexity than Forth,
but in exchange we get "normal" programming constructs such as functions,
variables and blocks.

In implementation, Woop is a result from many years of experimenting with
languages, intermediate representations and virtual machines. We're forever
grateful to the programming and computer science community which keeps on
publishing fascinating ideas.

## License

Woop is is available under the 0BSD license:

> Copyright (C) 2018 Magnus Holm <judofyr@gmail.com>
> 
> Permission to use, copy, modify, and/or distribute this software for any
> purpose with or without fee is hereby granted.
> 
> THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
> REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
> AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
> INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
> LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
> OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
> PERFORMANCE OF THIS SOFTWARE.

