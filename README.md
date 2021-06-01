# Brainf\*ck

This is a simple [Brainf\*ck](https://en.wikipedia.org/wiki/Brainfuck) interpreter in C which can detect and locate runtime errors.

## The Language

Brainf\*ck is a programming language created in 1993 by Urban Müller. It utilises a simple machine model, which consists of:

- A one-dimentional array of 30000 byte cells initialised to 0;
- A data pointer which points to the first element at the beginning of program execution;
- A program;
- An instruction pointer;
- An input stream (`stdin`);
- An output stream (`stdout`).

The eight single-character commands of the language are listed below. All the other characters are ignored. The commands in the program are executed sequentially unless a `[` or `]` command is encountered.

| Command | Description                                                                                                                                                                              |
| ------- | ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| `>`     | Increments the data pointer (to point to the next cell to the right).                                                                                                                    |
| `<`     | Decrements the data pointer (to point to the next cell to the left).                                                                                                                     |
| `+`     | Increments the byte at the data pointer.                                                                                                                                                 |
| `-`     | Decrements the byte at the data pointer.                                                                                                                                                 |
| `.`     | Outputs the byte at the data pointer as an [ASCII](https://en.wikipedia.org/wiki/ASCII) character.                                                                                       |
| `,`     | Accepts an ASCII character as one byte of input, storing its value in the byte at the data pointer.                                                                                      |
| `[`     | If the byte at the data pointer is zero, then instead of moving the instruction pointer forward to the next command, jumps it _forward_ to the command after the _matching_ `]` command. |
| `]`     | If the byte at the data pointer is nonzero, then instead of moving the instruction pointer forward to the next command, jumps it _back_ to the command after the _matching_ `[` command. |

See [Wikipedia](https://en.wikipedia.org/wiki/Brainfuck) for a more detailed explanation.

## To Build

### Building with GNU Make

The interpreter can be built with GNU Make as follows.

```bash
$ sudo apt install build-essential clang git
$ git clone https://github.com/ZhongRuoyu/Brainfuck.git
$ cd Brainfuck
$ make
```

The last `make` command generates an executable named `bf` in the working directory.

### Building Manually

On platforms like Windows where `make` is not well supported, the interpreter can still be built manually. To do so, `git clone` this repository or download a zipped archive. Open a terminal in its root directory and build the executable using all the source files in [/src](/src), with include path [/include](/include). For instance, using `clang` on Windows with PowerShell:

```powershell
clang src/*.c -I include -std=c11 -O2 -o bf.exe
```

## To Use

To use the interpreter, simply supply the path to the Brainf\*ck program as an argument. For instance, running the following...

```bash
$ bf test/hello.b
```

... executes the program at [test/hello.b](/test/hello.b), and generates the following output:

```bash
Hello World!
```

The interpreter has the capability to detect and locate runtime errors. For instance, interpreting the following program...

```brainfuck
        (pointer initially at location 0)
+++++   increment the value at cell 0 to 5
<       try decrementing the pointer
>       increment the pointer
[-]     reset the cell to 0
```

... generates the following error:

```bash
At Line 3, Column 1: error: decrementing pointer to inaccessible cell.
    <       try decrementing the pointer
    ^
```

Run `bf --help` to view the detailed help message on using the interpreter.

To execute the interpreter, you may need to key in its path as well.

## Licence

Copyright (c) 2021 Zhong Ruoyu.

Unless otherwise stated, the files in this repository are licensed under the [MIT License](/LICENSE).
