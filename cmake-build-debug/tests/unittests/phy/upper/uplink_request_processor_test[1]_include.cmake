if(EXISTS "/home/seoyul/srsRAN_Projects/cmake-build-debug/tests/unittests/phy/upper/uplink_request_processor_test[1]_tests.cmake")
  include("/home/seoyul/srsRAN_Projects/cmake-build-debug/tests/unittests/phy/upper/uplink_request_processor_test[1]_tests.cmake")
else()
  add_test(uplink_request_processor_test_NOT_BUILT uplink_request_processor_test_NOT_BUILT)
endif()
