# CMake generated Testfile for 
# Source directory: /home/seoyul/srsRAN_Projects/tests/unittests/pdcp
# Build directory: /home/seoyul/srsRAN_Projects/cmake-build-debug/tests/unittests/pdcp
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
include("/home/seoyul/srsRAN_Projects/cmake-build-debug/tests/unittests/pdcp/pdcp_tx_test[1]_include.cmake")
include("/home/seoyul/srsRAN_Projects/cmake-build-debug/tests/unittests/pdcp/pdcp_tx_empty_pool_test[1]_include.cmake")
include("/home/seoyul/srsRAN_Projects/cmake-build-debug/tests/unittests/pdcp/pdcp_rx_test[1]_include.cmake")
include("/home/seoyul/srsRAN_Projects/cmake-build-debug/tests/unittests/pdcp/pdcp_tx_metrics_test[1]_include.cmake")
include("/home/seoyul/srsRAN_Projects/cmake-build-debug/tests/unittests/pdcp/pdcp_rx_metrics_test[1]_include.cmake")
include("/home/seoyul/srsRAN_Projects/cmake-build-debug/tests/unittests/pdcp/pdcp_tx_status_report_test[1]_include.cmake")
include("/home/seoyul/srsRAN_Projects/cmake-build-debug/tests/unittests/pdcp/pdcp_rx_status_report_test[1]_include.cmake")
include("/home/seoyul/srsRAN_Projects/cmake-build-debug/tests/unittests/pdcp/pdcp_rx_reestablish_test[1]_include.cmake")
include("/home/seoyul/srsRAN_Projects/cmake-build-debug/tests/unittests/pdcp/pdcp_tx_reestablish_test[1]_include.cmake")
add_test(pdcp_tx_test "pdcp_tx_test")
set_tests_properties(pdcp_tx_test PROPERTIES  LABELS "tsan" _BACKTRACE_TRIPLES "/home/seoyul/srsRAN_Projects/tests/unittests/pdcp/CMakeLists.txt;26;add_test;/home/seoyul/srsRAN_Projects/tests/unittests/pdcp/CMakeLists.txt;0;")
add_test(pdcp_tx_empty_pool_test "pdcp_tx_empty_pool_test")
set_tests_properties(pdcp_tx_empty_pool_test PROPERTIES  LABELS "tsan" _BACKTRACE_TRIPLES "/home/seoyul/srsRAN_Projects/tests/unittests/pdcp/CMakeLists.txt;33;add_test;/home/seoyul/srsRAN_Projects/tests/unittests/pdcp/CMakeLists.txt;0;")
add_test(pdcp_rx_test "pdcp_rx_test")
set_tests_properties(pdcp_rx_test PROPERTIES  LABELS "tsan" _BACKTRACE_TRIPLES "/home/seoyul/srsRAN_Projects/tests/unittests/pdcp/CMakeLists.txt;40;add_test;/home/seoyul/srsRAN_Projects/tests/unittests/pdcp/CMakeLists.txt;0;")
add_test(pdcp_tx_metrics_test "pdcp_tx_metrics_test")
set_tests_properties(pdcp_tx_metrics_test PROPERTIES  LABELS "tsan" _BACKTRACE_TRIPLES "/home/seoyul/srsRAN_Projects/tests/unittests/pdcp/CMakeLists.txt;47;add_test;/home/seoyul/srsRAN_Projects/tests/unittests/pdcp/CMakeLists.txt;0;")
add_test(pdcp_rx_metrics_test "pdcp_rx_metrics_test")
set_tests_properties(pdcp_rx_metrics_test PROPERTIES  LABELS "tsan" _BACKTRACE_TRIPLES "/home/seoyul/srsRAN_Projects/tests/unittests/pdcp/CMakeLists.txt;54;add_test;/home/seoyul/srsRAN_Projects/tests/unittests/pdcp/CMakeLists.txt;0;")
add_test(pdcp_tx_status_report_test "pdcp_tx_status_report_test")
set_tests_properties(pdcp_tx_status_report_test PROPERTIES  LABELS "tsan" _BACKTRACE_TRIPLES "/home/seoyul/srsRAN_Projects/tests/unittests/pdcp/CMakeLists.txt;61;add_test;/home/seoyul/srsRAN_Projects/tests/unittests/pdcp/CMakeLists.txt;0;")
add_test(pdcp_rx_status_report_test "pdcp_rx_status_report_test")
set_tests_properties(pdcp_rx_status_report_test PROPERTIES  LABELS "tsan" _BACKTRACE_TRIPLES "/home/seoyul/srsRAN_Projects/tests/unittests/pdcp/CMakeLists.txt;68;add_test;/home/seoyul/srsRAN_Projects/tests/unittests/pdcp/CMakeLists.txt;0;")
add_test(pdcp_rx_reestablish_test "pdcp_rx_reestablish_test")
set_tests_properties(pdcp_rx_reestablish_test PROPERTIES  LABELS "tsan" _BACKTRACE_TRIPLES "/home/seoyul/srsRAN_Projects/tests/unittests/pdcp/CMakeLists.txt;75;add_test;/home/seoyul/srsRAN_Projects/tests/unittests/pdcp/CMakeLists.txt;0;")
add_test(pdcp_tx_reestablish_test "pdcp_tx_reestablish_test")
set_tests_properties(pdcp_tx_reestablish_test PROPERTIES  LABELS "tsan" _BACKTRACE_TRIPLES "/home/seoyul/srsRAN_Projects/tests/unittests/pdcp/CMakeLists.txt;82;add_test;/home/seoyul/srsRAN_Projects/tests/unittests/pdcp/CMakeLists.txt;0;")
set_directory_properties(PROPERTIES LABELS "pdcp")
