BFC
===

Copyright (c) 2016 Dennis Chen <barracks510@gmail.com>

Synopsis
--------

BFC stands for "Bad for Children", as BrainFuck should not be a child's first
programming language. BFC is the Fastest BrainFuck interpreter in Western
Massachusetts. It is based of of Oleg Mazonka's work on an optimized
interpreter. (Optimizing brainfuck implementation of dialect based on Daniel's
dbfi.)

Usage
-----

This interpreter can run in two ways: reading from `stdin` or reading from a
file with path given by argv[1]. In either case, the program and input to the
program have to be separated with ! e.g. ",.!a" prints 'a', except in
interactive mode. To use it in interactive mode, you may send and EOF character
to seperate the program from the program input.

Building
--------

This program can be compiled with NOLNR macro defined.  NOLNR disables
optimization of linear loops (where '<>' balanced), e.g. [->+>++<<].  Linear
loop is then executed in one step.


License
-------

BFC is licensed under the terms of the Apache Software License, Version 2.0.
See the `LICENSE` for the full text of this license.

This program uses code written by Oleg Mazonka released under the revised BSD
license.

    Oleg Mazonka 4 Dec 2006  http://mazonka.com/

