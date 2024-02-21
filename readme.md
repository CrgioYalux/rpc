### How it works
In Reverse Polish Notation, each operator follows its operands.  
An infix expression like:  
```
(1 + 2) * (4 - 5)
```
Is entered like:
```
1 2 + 4 5 - *
```

### Expected behavior for this tool
- Base use:
```bash
$ rpc 5 5 + 10 2 - *
$ rpc: 80
```

- Using the show steps flag (-s):
```bash
$ rpc -s 5 5 + 10 2 - *
$ rpc: 5 5 + 10 2 - *
$ rpc: 10 8 *
$ rpc: 80
```

### TODO
- [ ] Literally do the minimum.
- [ ] Add optional flags.
    - [ ] Show steps flag.

### Stuff learned
- Variables defined inside a loop point to the same memory address unless you call malloc which gives you a different memory address each time, or at least one that you are not using.
- While you lose access to the memory through the variable defined for it, if you did something with the address (e.g. assign it to something outside the loop scope) you can keep the allocated memory for accessing it later.
    - Since malloc gives addresses within the heap, those do not get freed automatically; this is because you generally have to manually free malloc-assigned memory unless the program ends.
    - The case would be different if the memory was allocated on the stack, let's say within a function call. Once the function is done, if you don't return the address to manage it outside, you lose it and any attempt to accessing the value once stored there would be [Undefined Behavior](https://en.cppreference.com/w/cpp/language/ub).
