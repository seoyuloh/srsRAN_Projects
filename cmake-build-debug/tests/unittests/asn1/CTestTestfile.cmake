# CMake generated Testfile for 
# Source directory: /home/seoyul/srsRAN_Projects/tests/unittests/asn1
# Build directory: /home/seoyul/srsRAN_Projects/cmake-build-debug/tests/unittests/asn1
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
include("/home/seoyul/srsRAN_Projects/cmake-build-debug/tests/unittests/asn1/asn1_rrc_nr_test[1]_include.cmake")
include("/home/seoyul/srsRAN_Projects/cmake-build-debug/tests/unittests/asn1/asn1_e1ap_test[1]_include.cmake")
include("/home/seoyul/srsRAN_Projects/cmake-build-debug/tests/unittests/asn1/asn1_e2ap_test[1]_include.cmake")
include("/home/seoyul/srsRAN_Projects/cmake-build-debug/tests/unittests/asn1/asn1_f1ap_test[1]_include.cmake")
include("/home/seoyul/srsRAN_Projects/cmake-build-debug/tests/unittests/asn1/asn1_ngap_test[1]_include.cmake")
include("/home/seoyul/srsRAN_Projects/cmake-build-debug/tests/unittests/asn1/asn1_cause_conversion_test[1]_include.cmake")
add_test(asn1_utils_test "asn1_utils_test")
set_tests_properties(asn1_utils_test PROPERTIES  _BACKTRACE_TRIPLES "/home/seoyul/srsRAN_Projects/tests/unittests/asn1/CMakeLists.txt;27;add_test;/home/seoyul/srsRAN_Projects/tests/unittests/asn1/CMakeLists.txt;0;")
set_directory_properties(PROPERTIES LABELS "asn1")
