if(EXISTS "/home/seoyul/srsRAN_Projects/cmake-build-debug/tests/unittests/fapi/validators/ul_tti_request_validator_test[1]_tests.cmake")
  include("/home/seoyul/srsRAN_Projects/cmake-build-debug/tests/unittests/fapi/validators/ul_tti_request_validator_test[1]_tests.cmake")
else()
  add_test(ul_tti_request_validator_test_NOT_BUILT ul_tti_request_validator_test_NOT_BUILT)
endif()
