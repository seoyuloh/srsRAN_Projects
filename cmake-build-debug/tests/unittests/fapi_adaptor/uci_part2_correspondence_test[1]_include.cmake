if(EXISTS "/home/seoyul/srsRAN_Projects/cmake-build-debug/tests/unittests/fapi_adaptor/uci_part2_correspondence_test[1]_tests.cmake")
  include("/home/seoyul/srsRAN_Projects/cmake-build-debug/tests/unittests/fapi_adaptor/uci_part2_correspondence_test[1]_tests.cmake")
else()
  add_test(uci_part2_correspondence_test_NOT_BUILT uci_part2_correspondence_test_NOT_BUILT)
endif()
