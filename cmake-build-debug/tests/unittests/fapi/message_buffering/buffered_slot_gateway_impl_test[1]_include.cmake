if(EXISTS "/home/seoyul/srsRAN_Projects/cmake-build-debug/tests/unittests/fapi/message_buffering/buffered_slot_gateway_impl_test[1]_tests.cmake")
  include("/home/seoyul/srsRAN_Projects/cmake-build-debug/tests/unittests/fapi/message_buffering/buffered_slot_gateway_impl_test[1]_tests.cmake")
else()
  add_test(buffered_slot_gateway_impl_test_NOT_BUILT buffered_slot_gateway_impl_test_NOT_BUILT)
endif()
