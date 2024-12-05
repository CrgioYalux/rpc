Using valgrind I have solved some memory leaks crimes I commited back when I first implemented this thing. These are some (others didn't get into the picture):

### Before
```bash
azul@azul-mint:~/learning/learn_c_the_hard_way/revisits_after_learning/rpc$ valgrind --leak-che
ck=full ./build/rpc 123 123 + 444 / 5 + 10 \*
==60834== Memcheck, a memory error detector
==60834== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==60834== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==60834== Command: ./build/rpc 123 123 + 444 / 5 + 10 *
==60834== 
==60834== Conditional jump or move depends on uninitialised value(s)
==60834==    at 0x1095E6: main (in /home/azul/learning/learn_c_the_hard_way/revisits_after_lear
ning/rpc/build/rpc)
==60834== 
Result: 100
==60834== 
==60834== HEAP SUMMARY:
==60834==     in use at exit: 240 bytes in 10 blocks
==60834==   total heap usage: 20 allocs, 10 frees, 1,480 bytes allocated
==60834== 
==60834== 24 bytes in 1 blocks are definitely lost in loss record 1 of 4
==60834==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==60834==    by 0x1096C4: new_stack (in /home/azul/learning/learn_c_the_hard_way/revisits_after
_learning/rpc/build/rpc)
==60834==    by 0x1094AB: main (in /home/azul/learning/learn_c_the_hard_way/revisits_after_lear
ning/rpc/build/rpc)
==60834== 
==60834== 24 bytes in 1 blocks are definitely lost in loss record 2 of 4
==60834==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==60834==    by 0x109A6B: new_node (in /home/azul/learning/learn_c_the_hard_way/revisits_after_
learning/rpc/build/rpc)
==60834==    by 0x1097F1: pop_node (in /home/azul/learning/learn_c_the_hard_way/revisits_after_
learning/rpc/build/rpc)
==60834==    by 0x10966C: main (in /home/azul/learning/learn_c_the_hard_way/revisits_after_lear
ning/rpc/build/rpc)
==60834== 
==60834== 96 bytes in 4 blocks are definitely lost in loss record 3 of 4
==60834==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==60834==    by 0x109A6B: new_node (in /home/azul/learning/learn_c_the_hard_way/revisits_after_
learning/rpc/build/rpc)
==60834==    by 0x1097F1: pop_node (in /home/azul/learning/learn_c_the_hard_way/revisits_after_
learning/rpc/build/rpc)
==60834==    by 0x109520: main (in /home/azul/learning/learn_c_the_hard_way/revisits_after_lear
ning/rpc/build/rpc)
==60834== 
==60834== 96 bytes in 4 blocks are definitely lost in loss record 4 of 4
==60834==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==60834==    by 0x109A6B: new_node (in /home/azul/learning/learn_c_the_hard_way/revisits_after_
learning/rpc/build/rpc)
==60834==    by 0x1097F1: pop_node (in /home/azul/learning/learn_c_the_hard_way/revisits_after_
learning/rpc/build/rpc)
==60834==    by 0x109538: main (in /home/azul/learning/learn_c_the_hard_way/revisits_after_lear
ning/rpc/build/rpc)
==60834== 
==60834== LEAK SUMMARY:
==60834==    definitely lost: 240 bytes in 10 blocks
==60834==    indirectly lost: 0 bytes in 0 blocks
==60834==      possibly lost: 0 bytes in 0 blocks
==60834==    still reachable: 0 bytes in 0 blocks
==60834==         suppressed: 0 bytes in 0 blocks
==60834== 
==60834== Use --track-origins=yes to see where uninitialised values come from
==60834== For lists of detected and suppressed errors, rerun with: -s
==60834== ERROR SUMMARY: 12 errors from 5 contexts (suppressed: 0 from 0)
```

### After

```bash
azul@azul-mint:~/learning/learn_c_the_hard_way/revisits_after_learning/rpc$ make rebuild
rm -r build/
make
make[1]: Entering directory '/home/azul/learning/learn_c_the_hard_way/revisits_after_learning/r
pc'
mkdir build/
gcc -o main.o -c src/main.c
gcc -o stack.o -c src/stack.c
gcc -o node.o -c src/node.c
gcc -o die.o -c src/die.c
gcc -o build/rpc main.o stack.o node.o die.o -Wall -Wextra -pedantic -std=c99 -lm
mv *.o build/
make[1]: Leaving directory '/home/azul/learning/learn_c_the_hard_way/revisits_after_learning/rp
c'
azul@azul-mint:~/learning/learn_c_the_hard_way/revisits_after_learning/rpc$ valgrind --leak-che
ck=full --track-origins=yes ./build/rpc 123 123 + 444 / 5 + 10 \*
==61643== Memcheck, a memory error detector
==61643== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==61643== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==61643== Command: ./build/rpc 123 123 + 444 / 5 + 10 *
==61643== 
Result: 100
==61643== 
==61643== HEAP SUMMARY:
==61643==     in use at exit: 216 bytes in 9 blocks
==61643==   total heap usage: 20 allocs, 11 frees, 1,480 bytes allocated
==61643== 
==61643== 24 bytes in 1 blocks are definitely lost in loss record 1 of 3
==61643==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==61643==    by 0x109A83: new_node (in /home/azul/learning/learn_c_the_hard_way/revisits_after
learning/rpc/build/rpc)
==61643==    by 0x109809: pop_node (in /home/azul/learning/learn_c_the_hard_way/revisits_after
learning/rpc/build/rpc)
==61643==    by 0x10966C: main (in /home/azul/learning/learn_c_the_hard_way/revisits_after_lea
ning/rpc/build/rpc)
==61643== 
==61643== 96 bytes in 4 blocks are definitely lost in loss record 2 of 3
==61643==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==61643==    by 0x109A83: new_node (in /home/azul/learning/learn_c_the_hard_way/revisits_after
learning/rpc/build/rpc)
==61643==    by 0x109809: pop_node (in /home/azul/learning/learn_c_the_hard_way/revisits_after
learning/rpc/build/rpc)
==61643==    by 0x109520: main (in /home/azul/learning/learn_c_the_hard_way/revisits_after_lea
ning/rpc/build/rpc)
==61643== 
==61643== 96 bytes in 4 blocks are definitely lost in loss record 3 of 3
==61643==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==61643==    by 0x109A83: new_node (in /home/azul/learning/learn_c_the_hard_way/revisits_after
learning/rpc/build/rpc)
==61643==    by 0x109809: pop_node (in /home/azul/learning/learn_c_the_hard_way/revisits_after
learning/rpc/build/rpc)
==61643==    by 0x109538: main (in /home/azul/learning/learn_c_the_hard_way/revisits_after_lea
ning/rpc/build/rpc)
==61643== 
==61643== LEAK SUMMARY:
==61643==    definitely lost: 216 bytes in 9 blocks
==61643==    indirectly lost: 0 bytes in 0 blocks
==61643==      possibly lost: 0 bytes in 0 blocks
==61643==    still reachable: 0 bytes in 0 blocks
==61643==         suppressed: 0 bytes in 0 blocks
==61643== 
==61643== For lists of detected and suppressed errors, rerun with: -s
==61643== ERROR SUMMARY: 3 errors from 3 contexts (suppressed: 0 from 0)
azul@azul-mint:~/learning/learn_c_the_hard_way/revisits_after_learning/rpc$ 
```
