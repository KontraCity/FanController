# Example files

## fancontroller.service
A `systemctl` example service that can be used to manage the executable. Should be installed in /etc/systemd/system and configured:
```
$ systemctl daemon-reload
$ systemctl start fancontroller
$ systemctl enable fancontroller
```
The `enable` command makes `systemctl` launch `FanController` on every startup of the system.
`FanController`'s logs can be checked by using:
```
$ systemctl status fancontroller
```
