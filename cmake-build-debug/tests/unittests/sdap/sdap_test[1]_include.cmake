if(EXISTS "/home/seoyul/srsRAN_Projects/cmake-build-debug/tests/unittests/sdap/sdap_test[1]_tests.cmake")
  include("/home/seoyul/srsRAN_Projects/cmake-build-debug/tests/unittests/sdap/sdap_test[1]_tests.cmake")
else()
  add_test(sdap_test_NOT_BUILT sdap_test_NOT_BUILT)
endif()
