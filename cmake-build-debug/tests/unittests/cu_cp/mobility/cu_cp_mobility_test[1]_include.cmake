if(EXISTS "/home/seoyul/srsRAN_Projects/cmake-build-debug/tests/unittests/cu_cp/mobility/cu_cp_mobility_test[1]_tests.cmake")
  include("/home/seoyul/srsRAN_Projects/cmake-build-debug/tests/unittests/cu_cp/mobility/cu_cp_mobility_test[1]_tests.cmake")
else()
  add_test(cu_cp_mobility_test_NOT_BUILT cu_cp_mobility_test_NOT_BUILT)
endif()
