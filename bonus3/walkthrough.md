```sh
./bonus3 ''
```
The program reads the content of `/home/user/end/.pass` and will use `atoi(argv[1])` as an index to null-terminate the flag. It will then compare our input and the flag null-terminated, if they're equal we'll get a shell. So we just need an empty string as an input, because `'' == ''`.
