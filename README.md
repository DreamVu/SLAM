# Simulatenous Localization & Mapping (SLAM)
SLAM with DreamVu [PAL](https://dreamvu.com/pal-usb/)

Please follow the instructions given below on any of the Nvidia Jetson embedded boards with Jetpack 4.4.1 to install the software.

## Step 1. Clone the repository 
-     sudo apt-get install git-lfs
      git clone https://github.com/DreamVu/Obstacle-Detection.git
      cd Obstacle-Detection
      git lfs pull
      
## Step 2. Installing Dependencies 
Confirm the following dependencies. These are must have to proceed further

- ### Jetpack 4.4.1
- ### Install Git-lfs before cloning this repo. 
-     sudo apt-get install git-lfs


- ### CUDA enabled OpenCV 4.4.0 and OpenCV Contrib 4.4.0 libraries. 
  Follow these steps to install the required OpenCV dependencies. 
-      cd installations
       chmod +x ./*.sh
       sudo ./opencv.sh

- ### Python 3.6 libraries (pytorch, torchvision, numpy, PIL, etc.)

## Step 3. Installing SLAM
      cd installations
      chmod +x ./*.sh
      sudo ./install.sh arg1 arg2

  - arg1: It can be either 0, 1 or can be skipped.  On selecting 1, installation will build the whole software based on the particular Nvidia Jetson architecture and will enable higher performance. This may take a few hours to complete the installation. On selecting 0, it will quickly build the software by using some of the pre-configured libraries provided. If arg1 is skipped, then arg2 must also be skipped.

  - arg2:  If the arg1 is 1, then the second argument takes in the amount of RAM the process will use during the build of the software in MBs. Following are the recommended values for different Nvidia Jetson architectures.
            For Jetson Xavier NX arg2: 3500
            For Jetson Xavier AGX arg2: 8000
            For Jetson Nano arg2: 1000
            
Once complete please reboot the system.

## Step 4. Installing Camera Data File 
The data files are delivered along with the purchase of the PAL camera. In case you have not received them, please request for the files by filling out a [form](https://support.dreamvu.com/portal/en/newticket)

      chmod +x setup.sh
      sudo ./setup.sh
      
## Documentation 
For rest of the evaluation of the SLAM software, please read the [Evaluation Manual](https://docs.google.com/document/d/e/2PACX-1vTkVh8fdDUcFPjEnIlgoYYGmfGXxehH17zJg5YPMLCTwIfoWStRAKG8NxfuL8-X9wbzz_BRc3cCwRXa/pub)

## Support 
If you need help or more informations check our [Help Center](https://support.dreamvu.com/portal/en/home) or join our [Community](https://support.dreamvu.com/portal/en/community/dreamvu-inc).

## Contributing
Feel free to open an issue if you find a bug, or a pull request for bug fixes, features or other improvements.
