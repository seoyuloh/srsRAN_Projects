if(EXISTS "/home/seoyul/srsRAN_Projects/cmake-build-debug/tests/unittests/e2/e2_subscription_setup_test[1]_tests.cmake")
  include("/home/seoyul/srsRAN_Projects/cmake-build-debug/tests/unittests/e2/e2_subscription_setup_test[1]_tests.cmake")
else()
  add_test(e2_subscription_setup_test_NOT_BUILT e2_subscription_setup_test_NOT_BUILT)
endif()
