if(EXISTS "/home/seoyul/srsRAN_Projects/cmake-build-debug/tests/unittests/pcap/pcap_rlc_test[1]_tests.cmake")
  include("/home/seoyul/srsRAN_Projects/cmake-build-debug/tests/unittests/pcap/pcap_rlc_test[1]_tests.cmake")
else()
  add_test(pcap_rlc_test_NOT_BUILT pcap_rlc_test_NOT_BUILT)
endif()
