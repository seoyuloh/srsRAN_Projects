if(EXISTS "/home/seoyul/srsRAN_Projects/cmake-build-debug/tests/unittests/rrc/rrc_ue_test[1]_tests.cmake")
  include("/home/seoyul/srsRAN_Projects/cmake-build-debug/tests/unittests/rrc/rrc_ue_test[1]_tests.cmake")
else()
  add_test(rrc_ue_test_NOT_BUILT rrc_ue_test_NOT_BUILT)
endif()
