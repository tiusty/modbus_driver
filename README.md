# Compiling for WSL 

## Setting up environment
WSL = (Windows Subsystem for Linux)

1. Install WSL from the Microsoft store in Windows 10.
    1. You can find it [here](https://www.microsoft.com/en-us/p/ubuntu/9nblggh4msv6?activetab=pivot:overviewtab)
2. Open Windows Power Shell as Administrator and run:
    1. Enable-WindowsOptionalFeature -Online -FeatureName Microsoft-Windows-Subsystem-Linux
    2. Then restart your computer
3. Run Ubuntu and setup a username/password
4. Install necessary tools:
    1. ```
        sudo apt-get update
        sudo apt-get install cmake gcc clang gdb build-essential git
       ```
5. Install libmodbus
    1. ``` sudo apt-get install libmodbus-dev```  
6. Now the modbus library should be installed and the program can be compiled/run

## Build+Run the executable
1. Open an Ubuntu terminal
    1. Just search Ubuntu on the Windows start menu
1. Setup SSH keys (maybe optional)
    1. https://docs.github.com/en/free-pro-team@latest/github/authenticating-to-github/generating-a-new-ssh-key-and-adding-it-to-the-ssh-agent
1. Clone the repo to the desired directory
    1. cd to desired directory
    2. clone the repo
        ``` git clone git@github.com:tiusty/modbus_driver.git ```
    3. Go to project root
        ```cd modbus_driver/```
        
2. Build+run the executable
    1. ``` 
        mkdir build
        cd build
        cmake ..
        make
        ./modbus_driver
        ```

## Notes
When running from WSL on a windows 10 machine, the com ports are accessible via WSl.   
The pattern goes as follows:  
COM1 = /dev/ttyS1  
COM2 = /dev/ttyS2  
COM3 = /dev/ttyS3  
etc...  
i.e the com ports are mapped to the /dev/ttyS* serial ports  
