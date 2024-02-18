### Functions as parameters  
```c
// Function declaration
void func(void (*cb)(int));

// Function definition
void func(void (*cb)(int)) {
    int b = 0;
    (*cb)(b);
}

// Function to pass as argument
void callback(int a) {
    /* do something */
    return;
}

// Function call
func(callback);
```
