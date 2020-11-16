# iShapes Demonstrator 
[TOC]

# What is it? 
iShapes is an interactive GUI based DDS (Data Distribution Service) Application to learn, demonstate and test dds key concepts.

It shows and demonstrates the key dds concepts and some of the key DDS Quality of Services (QoSs).
It has also been used at the OMG ( Object Management Group) to test the interoperability of the ADLINK DDS products with other compliant DDS implementations.

Each geometrical shape is represented by a dedicated dds topic such as a Circle, Triangle, etc ....

All the geometrical shapes share the same dataType. The dataType structure is modeled in an .idl file.

The shape dataType is characterized by its color, its position in a 2D space and its Size. 
Shapes with different colors are considered different data objects, i,e different data instances, as the color data attribute is considered the @Key of the dataType. Each data instance has its unique identity, its own lifecycle and its state.


# Building iShapes

The iShapes demo application code is common for ADLINK Vortex Opensplice and Cyclone DDS.  
ishapes can be rely on Cyclone DDS only, or Vortex Opensplice dds only, or you can run some ishapes instances with Cyclone and others with Opensplice typically if you want to test interoperability between the too products.

For the Cyclone Ishape demo, the Cyclone DDS C core, CXX Idl compiler and the C++ binding for Cyclone DDS need to be installed before proceeding.   
You can get Cyclone C Core from https://github.com/eclipse-cyclonedds/cyclonedds.git , the C++ IDL compiler from https://github.com/ADLINK-IST/idlpp-cxx/ and the related C++ APIs from https://github.com/eclipse-cyclonedds/cyclonedds-cxx

For Vortex Opensplice Ishape demo Vortex Opensplice DDS need to be installed before proceeding. you can download the Vortex Opensplice DDS from ADLINK Website : https://www.adlinktech.com/en/vortex-opensplice-data-distribution-service

To clone the ishape demo application in your locale repository, do  

      $ git clone https://github.com/atolab/dds-ishapes   
      $ cd Adlink_DDS_Demo_Ishapes   


## Building Cyclone DDS iShapes

From now one, we assume Cylone DDS or Vortex Opensplice and QT5 are installed

### Building on Linux/MacOS with cmake
To build the iShapes demo you need to have installed a QT5 development environment. The following QT5 environment variables has to be set in order to build and run ishapes:
      
      $ export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:<qt5_install-location>
      
       Where <qt5_install-location> is the installation directory of your QT5 installation , e.g (/usr/lib/x86_64_linux-gnu/qt5)  

then you need to simply do the following from the iShape demo root directory:

      $ mkdir cyclone_demo_ishapes && cd cyclone_demo_ishapes  
      $ cmake .. -DADLINK_DDS_PRODUCT=Cyclone -DCYCLONE_INSTALLED_DIR="<cxx_install-location>"  
      $ cmake --build . --config Release --target install  
      
      Where <cxx_install-location> is the location of Cyclone DDS C++ package  
      
     Note: please use '--config Debug' if you are using Cyclone DDS debug build to build this iShape application.

### Building on Windows with cmake
To build the demo you need to have installed a QT5 development environment. The following QT5 environment variables has to be set in order to build and run ishapes:

      C:\> set QTDIR=<QT5-INSTALLATION-DIR> 
      C:\> set QT_PLUGIN_PATH=<QT5-INSTALLATION-DIR>\plugins  
      C:\> set PATH=<QT5-INSTALLATION-DIR>\bin;%PATH%   
      
      Where <QT5-INSTALLATION-DIR> is the installation directory of your QT5 installation , e.g (<C:\Qt\5.7.1> )  

then you need to simply do the following from the iShape demo root directory:

      $ mkdir cyclone_demo_ishapes && cd cyclone_demo_ishapes  
      $ cmake .. -DADLINK_DDS_PRODUCT=Cyclone -DCYCLONE_INSTALLED_DIR="<cxx_install-location>"  
      $ cmake --build . --config Release --target install  
      
      Where <cxx_install-location> is the location of the Cyclone DDS C++ package  
      
      Note: please use '--config Debug' if you are using Cyclone DDS debug build to build this iShape application.

## Building Opensplice DDS iShapes

### Building on Linux/MacOS with cmake

To build the iShapes demo you need to have installed a QT5 development environment. The following QT5 environment variables has to be set in order to build and run ishapes:
      
      $ export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:<qt5_install-location>
      
       Where <qt5_install-location> is the installation directory of your QT5 installation , e.g (/usr/lib/x86_64_linux-gnu/qt5)  

then you need to simply do the following from the iShape demo root directory:

      $ source <ospl_install-location>/release.com  
      $ mkdir ospl_demo_ishapes && cd ospl_demo_ishapes  
      $ cmake .. -DADLINK_DDS_PRODUCT=Ospl  
      $ cmake --build . --config Release --target install  
      
      Where <ospl_install-location> is the location of Opensplice DDS Home directory.e. The corresponding Opensplice environment variable is OSPL_HOME. 
      
      Note: please use '--config Debug' if you are using Opensplice DDS debug build to build this iShape application.
  
### Building on Windows with cmake
To build the demo you need to have installed a QT5 development environment.  The following QT5 environment variables has to be set in order to build and run ishapes:

      C:\> set QTDIR=<QT5-INSTALLATION-DIR> 
      C:\> set QT_PLUGIN_PATH=<QT5-INSTALLATION-DIR>\plugins  
      C:\> set PATH=<QT5-INSTALLATION-DIR>\bin;%PATH%  
      C:\> "<ospl_install-location>"\release.bat  
      
      Where is the installation directory of your QT5 installation , e.g (<C:\Qt\5.7.1> )  

then you should need to simply do the following from the iShape demo root directory:

      $ "<ospl_install-location>"\release.bat  
      $ mkdir ospl_demo_ishapes && cd ospl_demo_ishapes  
      $ cmake .. -DADLINK_DDS_PRODUCT=Ospl  
      $ cmake --build . --config Release --target install  
      
      Where <ospl_install-location> is the location of Opensplice DDS Home directory.  
      
      Note: please use '--config Debug' if you are using Opensplice DDS debug build to build this iShape application.
      

# Running iShapes

The iShapes demo allows you to publish and subscribe instances of various shapes. The demo is didactic if you run it as at least into two application instances, thus from a shell do one of the below then have one of the applications publish some shapes and press the subscribe button on the other application to receive them.

image-20201022104103958

## Running Cyclone DDS iShapes
### Linux/MacOS:

To build the iShapes demo you need to have set the Cyclone DDS lib to the LD_LIBRARY_PATH. The following Cyclone environment variables has to be set in order to run ishapes:
      

      $ export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:<cxx_install-location>/lib
  
      Where <cxx_install-location> is the location of Cyclone DDS C++ package. 


cyclone_demo_ishapes is intalled in the <cxx_install-location>/bin directory of Cyclone installation. To run it  you should need to simply do the following:

      $ <cxx_install-location>/bin/cyclone_demo_ishapes &  
      $ <cxx_install-location>/bin/cyclone_demo_ishapes &  
  
Where <install-location> is the location of Cyclone DDS C++ package  

### Windows:
ospl_demo_ishapes is intalled in <cxxx_install-location>/bin directory of Eclipse Cyclone installation. To run it  you should need to simply do the following:  
      
      C:\> start <install-location>\bin\cyclone_demo_ishapes  
      C:\> start <install-location>\bin\cyclone_demo_ishapes  
  
Where <cxx_install-location> is the location of Cyclone DDS C++ package  

## Running Opensplice DDS iShapes
### Linux/MacOS:
ospl_demo_ishapes is available in <installation>/bin directory of Opensplice DDS installation directory. To run it you should need to simply do the following: 

      $ source <ospl_install-location>/release.com
      $ <ospl_install-location>/bin/ospl_demo_ishapes &
      $ <ospl_install-location>/bin/ospl_demo_ishapes &
  
      Where <ospl_install-location> is the location of Opensplice DDS Home directory.

### Windows:
      $ "<ospl_install-location>"\release.bat 
      C:\> start <ospl_install-location>\bin\ospl_demo_ishapes  
      C:\> start <ospl_install-location>\bin\ospl_demo_ishapes  
      
      Where <ospl_install-location> is the location of Opensplice DDS Home directory.
