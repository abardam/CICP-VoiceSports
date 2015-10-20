# CICP-VoiceSports

The main solution file is in CICP-VoiceSports/

# config.h

Modify config.h.in to create config.h

# KinectRead
This project contains methods for reading input from the Kinect v2. In order to use this, you need the [Kinect v2 SDK](http://www.microsoft.com/en-us/download/details.aspx?id=44561). You may be unable to install it if you are on Windows 7 or lower. I will provide a workaround with dummy functions.

After installing the SDK, the environment variables KINECTSDK2_INCLUDE and KINECTSDK2_LIB must be set to the proper paths. (Default: .../Program Files/Microsoft SDKs/Kinect/<version>/inc/, .../Program Files/Microsoft SDKs/Kinect/<version>/Lib/)