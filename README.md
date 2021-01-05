# How to using RS485 Communication with Ubuntu and Windows
This tutorial uses my own experiment and references through the internet to connect devices using RS485. My OS is Ubuntu 18.04. It's also easy to switch to Windows with some line.
# Process
1. Add libraries included C++ Library and Linux Library.
2. Establish connection and check wheter it's succesful or failed.
3. Send command content and command size if the connection is okay.
# Notes:
Run as root to access thoroughly.
```bash
sudo -s
```
To check the device name, run below command before and after plugging usb connection. Device name will be the missing name after removing usb.
```bash
ls /dev/tty*
```
Comments are added beside code.

References: https://blog.mbedded.ninja/programming/operating-systems/linux/linux-serial-ports-using-c-cpp/
