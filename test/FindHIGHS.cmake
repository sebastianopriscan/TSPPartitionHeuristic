if(WIN32)
        find_path(HIGHS_INCLUDE_DIR highs_c_api.h
                PATHS

        )

        find_library(HIGHS_LIBRARIES NAMES libhighs
        )
else(WIN32)
        find_path(HIGHS_INCLUDE_DIR Highs.h
                PATHS
                ${HIGHS_SOURCE_DIR}/HiGHS/src
                ${HIGHS_INSTALL_DIR}/include/highs
                /usr/local/include/highs
        )

        find_library(HIGHS_LIBRARIES NAMES highs
                PATHS
                ${HIGHS_SOURCE_DIR}/HiGHS/build/lib
                ${HIGHS_INSTALL_DIR}*/include/highs/interfaces
                /usr/local/lib
        )
endif(WIN32)