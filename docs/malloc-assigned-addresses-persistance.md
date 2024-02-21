### Malloc-Assigned Addresses Persistance

- Variables defined inside a loop point to the same memory address unless you call malloc which gives you a different memory address each time, or at least one that you are not using.

```c
int main(void) {
    for (int i = 0; i < 10; i++) {
        int x = i * 2;
        int *pX = &x; // always 0xTheSame

        int *y = malloc(sizeof(int)); // 0xChangesEachIteration
    }
}
```

- While you lose access to the memory through the variable defined for it, if you did something with the address (e.g. assign it to something outside the loop scope) you can keep the allocated memory for accessing it later.
    - Since malloc gives addresses within the heap, those do not get freed automatically; this is because you generally have to manually free malloc-assigned memory unless the program ends.
    - The case would be different if the memory was allocated on the stack, let's say within a function call. Once the function is done, if you don't return the address to manage it outside, you lose it and any attempt to accessing the value once stored there would be [Undefined Behavior](https://en.cppreference.com/w/cpp/language/ub).
