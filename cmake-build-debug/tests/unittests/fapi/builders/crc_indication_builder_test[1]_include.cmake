if(EXISTS "/home/seoyul/srsRAN_Projects/cmake-build-debug/tests/unittests/fapi/builders/crc_indication_builder_test[1]_tests.cmake")
  include("/home/seoyul/srsRAN_Projects/cmake-build-debug/tests/unittests/fapi/builders/crc_indication_builder_test[1]_tests.cmake")
else()
  add_test(crc_indication_builder_test_NOT_BUILT crc_indication_builder_test_NOT_BUILT)
endif()
