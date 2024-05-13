# FanController
FanController is an executable that controls Raspberry Pi CPU cooling fan.
It continuously monitors CPU temperature and turns fan on only when the Pi is under heavy load and hot.

### Dependencies
* [libfmt](https://github.com/fmtlib/fmt)
* [libwiringpi](https://github.com/WiringPi/WiringPi)
* [libspdlog](https://github.com/gabime/spdlog)

### Compilation
```
$ mkdir build && cd build
$ cmake .. -DCMAKE_BUILD_TYPE=Release
$ make -j
```

### Installation
It's up to you how you install the controller.
It needs to run continuously and to have configuration file `/etc/fancontroller.conf`.
For example, `FanController` executable can be put in `/usr/local/bin` and `systemctl` service `/etc/systemd/system/fancontroller.service` can be created.
Don't forget to generate configuration file with `./FanController --generate`.

## How it works?
It peeks CPU temperature (`/sys/class/thermal/thermal_zone0/temp` file) every check interval that can be configured in configuration file.
For heavy loads when CPU temperature meets maximum configured temperature, controller turns fan on.
When Raspberry Pi load is light, fan stays off to preserve its life.

## Configuration
Fan controller's configuration file is `/etc/fancontroller.conf`.
Fan control pin, min/max temperatures and check interval can be configured there.
Can be created using:
```
$ ./FanController --generate
```

## Example files
Example fan controller `systemctl` service can be found in `files/` directory.
