if(EXISTS "/home/seoyul/srsRAN_Projects/cmake-build-debug/tests/unittests/pdcp/pdcp_rx_metrics_test[1]_tests.cmake")
  include("/home/seoyul/srsRAN_Projects/cmake-build-debug/tests/unittests/pdcp/pdcp_rx_metrics_test[1]_tests.cmake")
else()
  add_test(pdcp_rx_metrics_test_NOT_BUILT pdcp_rx_metrics_test_NOT_BUILT)
endif()
