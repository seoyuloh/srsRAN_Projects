if(EXISTS "/home/seoyul/srsRAN_Projects/cmake-build-debug/tests/unittests/fapi/builders/dl_pdcch_builder_test[1]_tests.cmake")
  include("/home/seoyul/srsRAN_Projects/cmake-build-debug/tests/unittests/fapi/builders/dl_pdcch_builder_test[1]_tests.cmake")
else()
  add_test(dl_pdcch_builder_test_NOT_BUILT dl_pdcch_builder_test_NOT_BUILT)
endif()
