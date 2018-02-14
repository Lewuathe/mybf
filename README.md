BrainFuck in LLVM
====

This is a implementation of [BrainFuck](https://en.wikipedia.org/wiki/Brainfuck) in LLVM.

# How to build

```
$ mkdir build
$ cd build
$ cmake ..
$ make
``` 

# Usage

```
$ echo '--<-<<+[+[<+>--->->->-<<<]>]<<--.<++++++.<<-..<<.<+.>>.>>.<<<.+++.>>.>>-.<<<+.' | ./mybf | lli
Hello, World!
```

# LICENSE

[MIT License](https://opensource.org/licenses/MIT)