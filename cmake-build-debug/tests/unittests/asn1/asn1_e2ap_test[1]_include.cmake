if(EXISTS "/home/seoyul/srsRAN_Projects/cmake-build-debug/tests/unittests/asn1/asn1_e2ap_test[1]_tests.cmake")
  include("/home/seoyul/srsRAN_Projects/cmake-build-debug/tests/unittests/asn1/asn1_e2ap_test[1]_tests.cmake")
else()
  add_test(asn1_e2ap_test_NOT_BUILT asn1_e2ap_test_NOT_BUILT)
endif()
