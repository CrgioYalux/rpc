### How it works
In [Reverse Polish Notation](https://en.wikipedia.org/wiki/Reverse_Polish_notation), each operator follows its operands.  
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
$ Result: 80
$ rpc 5 5 + 0 /
$ Error: attempt to divide by 0.
$ rcp 123 123 \* 123 - 444 / # need to use \* to escape character
$ Result: 33
```

- Using the show steps flag (-s):
```bash
$ rpc -s 5 5 + 10 2 - *
$ rpc: 5 5 + 10 2 - *
$ rpc: 10 8 *
$ rpc: 80
```

### TODO
- [x] Literally do the minimum.
- [ ] Add optional flags.
    - [ ] Show steps flag.
- [ ] Support floating-point numbers

### Stuff learned
- [Functions as Parameteres](/docs/function-as-parameters.md)
- [Malloc-Assigned Addresses Persistance](/docs/malloc-assigned-addresses-persistance.md)
- [About `const type *`](/docs/const_type_*.md)
