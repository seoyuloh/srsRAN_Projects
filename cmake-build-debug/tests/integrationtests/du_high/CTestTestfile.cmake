# CMake generated Testfile for 
# Source directory: /home/seoyul/srsRAN_Projects/tests/integrationtests/du_high
# Build directory: /home/seoyul/srsRAN_Projects/cmake-build-debug/tests/integrationtests/du_high
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(du_high_test "du_high_test")
set_tests_properties(du_high_test PROPERTIES  LABELS "tsan" _BACKTRACE_TRIPLES "/home/seoyul/srsRAN_Projects/tests/integrationtests/du_high/CMakeLists.txt;44;add_test;/home/seoyul/srsRAN_Projects/tests/integrationtests/du_high/CMakeLists.txt;0;")
add_test(mac_test_mode_adapter_test "mac_test_mode_adapter_test")
set_tests_properties(mac_test_mode_adapter_test PROPERTIES  _BACKTRACE_TRIPLES "/home/seoyul/srsRAN_Projects/tests/integrationtests/du_high/CMakeLists.txt;50;add_test;/home/seoyul/srsRAN_Projects/tests/integrationtests/du_high/CMakeLists.txt;0;")
set_directory_properties(PROPERTIES LABELS "du_high;integrationtest")
