# Brainf\*ck

This is a simple [Brainf\*ck](https://en.wikipedia.org/wiki/Brainfuck) interpreter in C which supports error detection.

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

To build the interpreter, simply include all the source files in the root directory. For instance:

```
clang *.c -o bf
```

## To Use

To use the interpreter, simply supply the path to the Brainf\*ck program as an argument. For instance, running the following...

```
bf test/hello.b
```

... executes the program at [test/hello.b](/test/hello.b), and generates the following output:

```
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

```
At Line 3, Column 1: error: decrementing pointer to inaccessible cell.
    <       try decrementing the pointer
    ^
```

Run `bf --help` to view the detailed help message on using the interpreter.

## Licence

Copyright (c) 2021 Zhong Ruoyu.

Unless otherwise stated, the files in this repository are licensed under the MIT License.
