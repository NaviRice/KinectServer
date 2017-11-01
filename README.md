# KinectServer
Server to distribute kinect's incoming images.

### Prerequisites
[Kinect -> libfreenect2](https://github.com/OpenKinect/libfreenect2)  
[Protobuf(Google)](https://github.com/google/protobuf)

### How to compile
This project uses cmake so:

    mkdir build
    cmake ..
    make
  
  And you are all set. if the compilation fails you probably didn't install the prerequisites.
  
### To run
Make sure you connected the kinnect to your computer(USB 3)
Run the kinect_server program as sudo
    
    sudo ./kinect_server
    
if you see the "Setting new image" message in your terminal you are all set.

now you can run your program with the given port to download the latest incoming image set.
