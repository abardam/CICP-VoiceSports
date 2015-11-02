# VoiceSports

The main solution file is in VoiceSports/

# config.h

Modify config.h.in to create config.h.

*Current settings:*
* _USE_KINECT: define this in order to make use of Kinect functions.

# KinectRead
This project contains methods for reading input from the Kinect v2. In order to use this, you need the [Kinect v2 SDK](http://www.microsoft.com/en-us/download/details.aspx?id=44561). You may be unable to install it if you are on Windows 7 or lower. I will provide a workaround with dummy functions.

After installing the SDK, the environment variables KINECTSDK2_INCLUDE and KINECTSDK2_LIB must be set to the proper paths. (Default: .../Program Files/Microsoft SDKs/Kinect/<version>/inc/, .../Program Files/Microsoft SDKs/Kinect/<version>/Lib/)

# Speech recognition
## Setup
1. Install python
2. Add python directory into your PATH environment ((how)[http://windowsitpro.com/systems-management/how-can-i-add-new-folder-my-system-path])
3. Open command window and type __python__ to make sure python has been configure correctly.
4. Run the following commands on command window:
```
python -m pip install pyaudio
python -m pip install ws4py==0.3.2
python -m pip install git+https://truongdq@bitbucket.org/truongdq/python_kaldi_client.git
```
5. Run Tools/ASR/simple-asr.py (double click or run from a command window)