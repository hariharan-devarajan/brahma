#-----------------------------------------------------------------------------
# Version file for install directory
#-----------------------------------------------------------------------------
set(PACKAGE_VERSION 4.1.2)

if ("${PACKAGE_FIND_VERSION_MAJOR}" EQUAL 4)
    set(PACKAGE_VERSION_COMPATIBLE 1)
    if ("${PACKAGE_FIND_VERSION_PATCH}" EQUAL 2)
        set(PACKAGE_VERSION_EXACT 1)
    endif ()
endif ()
