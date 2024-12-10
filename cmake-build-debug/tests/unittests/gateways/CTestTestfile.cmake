# CMake generated Testfile for 
# Source directory: /home/seoyul/srsRAN_Projects/tests/unittests/gateways
# Build directory: /home/seoyul/srsRAN_Projects/cmake-build-debug/tests/unittests/gateways
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(sctp_network_gateway_test "sctp_network_gateway_test")
set_tests_properties(sctp_network_gateway_test PROPERTIES  LABELS "tsan" _BACKTRACE_TRIPLES "/home/seoyul/srsRAN_Projects/tests/unittests/gateways/CMakeLists.txt;29;add_test;/home/seoyul/srsRAN_Projects/tests/unittests/gateways/CMakeLists.txt;0;")
add_test(udp_network_gateway_test "udp_network_gateway_test")
set_tests_properties(udp_network_gateway_test PROPERTIES  LABELS "tsan" _BACKTRACE_TRIPLES "/home/seoyul/srsRAN_Projects/tests/unittests/gateways/CMakeLists.txt;34;add_test;/home/seoyul/srsRAN_Projects/tests/unittests/gateways/CMakeLists.txt;0;")
add_test(udp_network_gateway_pool_depletion_test "udp_network_gateway_pool_depletion_test")
set_tests_properties(udp_network_gateway_pool_depletion_test PROPERTIES  LABELS "tsan" _BACKTRACE_TRIPLES "/home/seoyul/srsRAN_Projects/tests/unittests/gateways/CMakeLists.txt;39;add_test;/home/seoyul/srsRAN_Projects/tests/unittests/gateways/CMakeLists.txt;0;")
set_directory_properties(PROPERTIES LABELS "gateways")
