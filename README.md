Ray Tracing in One Weekend.

Temp README.md file with basic _informal_ information.

The project is using CMake in Visual Studio 2022 and is targeting C++ 20.

- Open cmake-gui (or by command line, whichever you prefer).
- Configure and Generate the project in a `/root directory/build/` folder.
- Navigate to the `/root/build/` folder, and open the Visual Studio solution (.sln).
- Go to "RayTracing" project, right-click and "Set as Startup Project".
- Build and run.

For now, running the project will output in the console the numbers of the (int)RGB values. To get the `.ppm` image file:

- Go to `/root directory/bin/Debug/ (or Release, whichever you built)`.
- In a console (e.g. press CTRL + ` in Visual Studio 2022 to open the Developer PowerShell), type: ```./RayTracing.exe > ../../images/image.ppm```

Since the file is written to the standard output stream, we need to redirect it to an image file. Specifically, this image file will be located in the `/root directory/images/` folder. To see an actual image (and not just plain numbers in text), use a PPM Viewer and open the `image.ppm` file.