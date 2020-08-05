Compiling for WSL 
--------------------------------------------
WSL = (Windows Subsystem for Linux)

1. Install WSl from the Microsoft store in Windows 10.
    1. You can find it [here](https://www.microsoft.com/en-us/p/ubuntu/9nblggh4msv6?activetab=pivot:overviewtab)
2. Open Windows Power Shell as Administrator and run:
    1. Enable-WindowsOptionalFeature -Online -FeatureName Microsoft-Windows-Subsystem-Linux
    2. Then restart your computer
3. Run Ubuntu and setup a username/password
4. Install necessary tools:
    1. ```
        sudo apt-get update
        sudo apt-get install cmake gcc clang gdb build-essential
       ```
5. Install libmodbus
    1. ``` sudo apt-get install libmodbus-dev```  
6. Now the modbus library should be installed and the program can be compiled/run
