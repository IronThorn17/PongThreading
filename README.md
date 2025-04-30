# PongThreading

PongThreading is a simple Pong game implemented using OpenGL and GLFW, featuring CPU threading for enhanced performance.

## Dependencies

Before running the project, ensure you have the following dependencies installed:

- [GLFW](https://www.glfw.org/): GLFW is a multi-platform library for creating windows with OpenGL contexts and managing input.

### GLFW Installation

Download GLFW from the [official website](https://www.glfw.org/download) or install it using a package manager.


#### Running GoogleTest using CMake ####
1) Install GLFW 3.4 as specified above. Make sure that GLFW is stored somewhere accessible.
        Ensure CMake v3.14 or newer is downloaded (CMake extension in VSCode or Visual Studio).

2) If using VSCode, install CMake Tools and either either Visual Studio 2022 or the Build Tools only. 
        --> https://visualstudio.microsoft.com/visual-cpp-build-tools/
        **Be sure to check C++ development when running the installer.** 
        To configure VSCode hit ctrl+shift+P --> CMake: Select a Kit and select Visual Studio Community

3) We need to edit the CMakeLists.txt file to fit your environment: 
        Make sure the CMakeLists.txt file specifies your filepath to GLFW 
            This line --> set(GLFW_DIR "C:/Users/Zak/glfw-3.4") # Change to desired filepath
        **Remove the comments under add_executables to include all the game files when ready to run tests on the full game!**

4) There should be a button in the bottom blue bar labeled "Build", click it to build the project. A green arrow should appear next to add_test() 
    in the CMakeLists file, click it to run the tests.
        **Or: Ctrl+shift+P --> Test: Run All Tests**

5) The project should run and return an output in the terminal. 

6) If new test files are added, be sure to add the path to the add_executables list before building and running again.
