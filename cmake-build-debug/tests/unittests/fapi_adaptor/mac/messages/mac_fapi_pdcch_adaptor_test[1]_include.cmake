if(EXISTS "/home/seoyul/srsRAN_Projects/cmake-build-debug/tests/unittests/fapi_adaptor/mac/messages/mac_fapi_pdcch_adaptor_test[1]_tests.cmake")
  include("/home/seoyul/srsRAN_Projects/cmake-build-debug/tests/unittests/fapi_adaptor/mac/messages/mac_fapi_pdcch_adaptor_test[1]_tests.cmake")
else()
  add_test(mac_fapi_pdcch_adaptor_test_NOT_BUILT mac_fapi_pdcch_adaptor_test_NOT_BUILT)
endif()
