# CMake generated Testfile for 
# Source directory: C:/Users/Zak/Desktop/PongThreading
# Build directory: C:/Users/Zak/Desktop/PongThreading/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
if(CTEST_CONFIGURATION_TYPE MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  add_test(PongTests "C:/Users/Zak/Desktop/PongThreading/build/Debug/runTests.exe")
  set_tests_properties(PongTests PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/Zak/Desktop/PongThreading/CMakeLists.txt;56;add_test;C:/Users/Zak/Desktop/PongThreading/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  add_test(PongTests "C:/Users/Zak/Desktop/PongThreading/build/Release/runTests.exe")
  set_tests_properties(PongTests PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/Zak/Desktop/PongThreading/CMakeLists.txt;56;add_test;C:/Users/Zak/Desktop/PongThreading/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
  add_test(PongTests "C:/Users/Zak/Desktop/PongThreading/build/MinSizeRel/runTests.exe")
  set_tests_properties(PongTests PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/Zak/Desktop/PongThreading/CMakeLists.txt;56;add_test;C:/Users/Zak/Desktop/PongThreading/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
  add_test(PongTests "C:/Users/Zak/Desktop/PongThreading/build/RelWithDebInfo/runTests.exe")
  set_tests_properties(PongTests PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/Zak/Desktop/PongThreading/CMakeLists.txt;56;add_test;C:/Users/Zak/Desktop/PongThreading/CMakeLists.txt;0;")
else()
  add_test(PongTests NOT_AVAILABLE)
endif()
subdirs("_deps/googletest-build")
