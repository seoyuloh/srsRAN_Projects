if(EXISTS "/home/seoyul/srsRAN_Projects/cmake-build-debug/tests/unittests/fapi/validators/slot_indication_validator_test[1]_tests.cmake")
  include("/home/seoyul/srsRAN_Projects/cmake-build-debug/tests/unittests/fapi/validators/slot_indication_validator_test[1]_tests.cmake")
else()
  add_test(slot_indication_validator_test_NOT_BUILT slot_indication_validator_test_NOT_BUILT)
endif()
