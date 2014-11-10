# Install script for directory: /usr/projects/plfs/rrz/plfs/plfs-2.5-mdhim

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "/usr/local")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "Release")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

# Install shared libraries without execute permission?
IF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  SET(CMAKE_INSTALL_SO_NO_EXE "0")
ENDIF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libplfs.so.2.5.1")
    FILE(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libplfs.so.2.5.1"
         RPATH "/usr/local/lib")
  ENDIF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libplfs.so.2.5.1")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES
    "/usr/projects/plfs/rrz/plfs/plfs-2.5-mdhim/lib/libplfs.so.2.5.1"
    "/usr/projects/plfs/rrz/plfs/plfs-2.5-mdhim/lib/libplfs.so.2.5"
    "/usr/projects/plfs/rrz/plfs/plfs-2.5-mdhim/lib/libplfs.so"
    )
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libplfs.so.2.5.1")
    FILE(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libplfs.so.2.5.1"
         OLD_RPATH "::::::::::::::"
         NEW_RPATH "/usr/local/lib")
    IF(CMAKE_INSTALL_DO_STRIP)
      EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libplfs.so.2.5.1")
    ENDIF(CMAKE_INSTALL_DO_STRIP)
  ENDIF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libplfs.so.2.5.1")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/usr/projects/plfs/rrz/plfs/plfs-2.5-mdhim/lib/libplfs.a")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/sbin/plfs")
    FILE(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/sbin/plfs"
         RPATH "/usr/local/lib")
  ENDIF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/sbin/plfs")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/sbin" TYPE EXECUTABLE FILES "/usr/projects/plfs/rrz/plfs/plfs-2.5-mdhim/bin/plfs")
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/sbin/plfs")
    FILE(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/sbin/plfs"
         OLD_RPATH "/lib64:/usr/projects/plfs/rrz/plfs/plfs-2.5-mdhim/lib"
         NEW_RPATH "/usr/local/lib")
    IF(CMAKE_INSTALL_DO_STRIP)
      EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/sbin/plfs")
    ENDIF(CMAKE_INSTALL_DO_STRIP)
  ENDIF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/sbin/plfs")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/plfs_check_config")
    FILE(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/plfs_check_config"
         RPATH "/usr/local/lib")
  ENDIF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/plfs_check_config")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/usr/projects/plfs/rrz/plfs/plfs-2.5-mdhim/bin/plfs_check_config")
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/plfs_check_config")
    FILE(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/plfs_check_config"
         OLD_RPATH "/usr/projects/plfs/rrz/plfs/plfs-2.5-mdhim/lib"
         NEW_RPATH "/usr/local/lib")
    IF(CMAKE_INSTALL_DO_STRIP)
      EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/plfs_check_config")
    ENDIF(CMAKE_INSTALL_DO_STRIP)
  ENDIF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/plfs_check_config")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/plfs_flatten_index")
    FILE(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/plfs_flatten_index"
         RPATH "/usr/local/lib")
  ENDIF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/plfs_flatten_index")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/usr/projects/plfs/rrz/plfs/plfs-2.5-mdhim/bin/plfs_flatten_index")
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/plfs_flatten_index")
    FILE(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/plfs_flatten_index"
         OLD_RPATH "/usr/projects/plfs/rrz/plfs/plfs-2.5-mdhim/lib"
         NEW_RPATH "/usr/local/lib")
    IF(CMAKE_INSTALL_DO_STRIP)
      EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/plfs_flatten_index")
    ENDIF(CMAKE_INSTALL_DO_STRIP)
  ENDIF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/plfs_flatten_index")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/plfs_ls")
    FILE(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/plfs_ls"
         RPATH "/usr/local/lib")
  ENDIF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/plfs_ls")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/usr/projects/plfs/rrz/plfs/plfs-2.5-mdhim/bin/plfs_ls")
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/plfs_ls")
    FILE(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/plfs_ls"
         OLD_RPATH "/usr/projects/plfs/rrz/plfs/plfs-2.5-mdhim/lib"
         NEW_RPATH "/usr/local/lib")
    IF(CMAKE_INSTALL_DO_STRIP)
      EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/plfs_ls")
    ENDIF(CMAKE_INSTALL_DO_STRIP)
  ENDIF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/plfs_ls")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/plfs_version")
    FILE(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/plfs_version"
         RPATH "/usr/local/lib")
  ENDIF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/plfs_version")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/usr/projects/plfs/rrz/plfs/plfs-2.5-mdhim/bin/plfs_version")
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/plfs_version")
    FILE(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/plfs_version"
         OLD_RPATH "/usr/projects/plfs/rrz/plfs/plfs-2.5-mdhim/lib"
         NEW_RPATH "/usr/local/lib")
    IF(CMAKE_INSTALL_DO_STRIP)
      EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/plfs_version")
    ENDIF(CMAKE_INSTALL_DO_STRIP)
  ENDIF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/plfs_version")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES "/usr/projects/plfs/rrz/plfs/plfs-2.5-mdhim/plfs.h")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES "/usr/projects/plfs/rrz/plfs/plfs-2.5-mdhim/src/plfs_error.h")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/plfs" TYPE FILE FILES
    "/usr/projects/plfs/rrz/plfs/plfs-2.5-mdhim/src/Mlog/mlogfacs.h"
    "/usr/projects/plfs/rrz/plfs/plfs-2.5-mdhim/src/plfs_internal.h"
    "/usr/projects/plfs/rrz/plfs/plfs-2.5-mdhim/src/Util.h"
    "/usr/projects/plfs/rrz/plfs/plfs-2.5-mdhim/src/COPYRIGHT.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/man/man1" TYPE FILE FILES
    "/usr/projects/plfs/rrz/plfs/plfs-2.5-mdhim/share/man/man1/plfs.1"
    "/usr/projects/plfs/rrz/plfs/plfs-2.5-mdhim/share/man/man1/plfs_check_config.1"
    "/usr/projects/plfs/rrz/plfs/plfs-2.5-mdhim/share/man/man1/plfs_ls.1"
    "/usr/projects/plfs/rrz/plfs/plfs-2.5-mdhim/share/man/man1/plfs_query.1"
    "/usr/projects/plfs/rrz/plfs/plfs-2.5-mdhim/share/man/man1/plfs_version.1"
    "/usr/projects/plfs/rrz/plfs/plfs-2.5-mdhim/share/man/man1/plfs_flatten_index.1"
    "/usr/projects/plfs/rrz/plfs/plfs-2.5-mdhim/share/man/man1/plfs_map.1"
    "/usr/projects/plfs/rrz/plfs/plfs-2.5-mdhim/share/man/man1/plfs_recover.1"
    "/usr/projects/plfs/rrz/plfs/plfs-2.5-mdhim/share/man/man1/dcon.1"
    "/usr/projects/plfs/rrz/plfs/plfs-2.5-mdhim/share/man/man1/findmesgbuf.1"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/man/man3" TYPE FILE FILES
    "/usr/projects/plfs/rrz/plfs/plfs-2.5-mdhim/share/man/man3/plfs.3"
    "/usr/projects/plfs/rrz/plfs/plfs-2.5-mdhim/share/man/man3/is_plfs_path.3"
    "/usr/projects/plfs/rrz/plfs/plfs-2.5-mdhim/share/man/man3/plfs_chown.3"
    "/usr/projects/plfs/rrz/plfs/plfs-2.5-mdhim/share/man/man3/plfs_flatten_index.3"
    "/usr/projects/plfs/rrz/plfs/plfs-2.5-mdhim/share/man/man3/plfs_mode.3"
    "/usr/projects/plfs/rrz/plfs/plfs-2.5-mdhim/share/man/man3/plfs_rename.3"
    "/usr/projects/plfs/rrz/plfs/plfs-2.5-mdhim/share/man/man3/plfs_symlink.3"
    "/usr/projects/plfs/rrz/plfs/plfs-2.5-mdhim/share/man/man3/plfs_write.3"
    "/usr/projects/plfs/rrz/plfs/plfs-2.5-mdhim/share/man/man3/plfs_close.3"
    "/usr/projects/plfs/rrz/plfs/plfs-2.5-mdhim/share/man/man3/plfs_getattr.3"
    "/usr/projects/plfs/rrz/plfs/plfs-2.5-mdhim/share/man/man3/plfs_getxattr.3"
    "/usr/projects/plfs/rrz/plfs/plfs-2.5-mdhim/share/man/man3/plfs_open.3"
    "/usr/projects/plfs/rrz/plfs/plfs-2.5-mdhim/share/man/man3/plfs_rmdir.3"
    "/usr/projects/plfs/rrz/plfs/plfs-2.5-mdhim/share/man/man3/plfs_sync.3"
    "/usr/projects/plfs/rrz/plfs/plfs-2.5-mdhim/share/man/man3/plfs_create.3"
    "/usr/projects/plfs/rrz/plfs/plfs-2.5-mdhim/share/man/man3/plfs_query.3"
    "/usr/projects/plfs/rrz/plfs/plfs-2.5-mdhim/share/man/man3/plfs_trunc.3"
    "/usr/projects/plfs/rrz/plfs/plfs-2.5-mdhim/share/man/man3/plfs_opendir_c.3"
    "/usr/projects/plfs/rrz/plfs/plfs-2.5-mdhim/share/man/man3/plfs_readdir_c.3"
    "/usr/projects/plfs/rrz/plfs/plfs-2.5-mdhim/share/man/man3/plfs_closedir_c.3"
    "/usr/projects/plfs/rrz/plfs/plfs-2.5-mdhim/share/man/man3/plfs_access.3"
    "/usr/projects/plfs/rrz/plfs/plfs-2.5-mdhim/share/man/man3/plfs_link.3"
    "/usr/projects/plfs/rrz/plfs/plfs-2.5-mdhim/share/man/man3/plfs_read.3"
    "/usr/projects/plfs/rrz/plfs/plfs-2.5-mdhim/share/man/man3/plfs_unlink.3"
    "/usr/projects/plfs/rrz/plfs/plfs-2.5-mdhim/share/man/man3/plfs_get_filetype.3"
    "/usr/projects/plfs/rrz/plfs/plfs-2.5-mdhim/share/man/man3/plfs_readdir.3"
    "/usr/projects/plfs/rrz/plfs/plfs-2.5-mdhim/share/man/man3/plfs_utime.3"
    "/usr/projects/plfs/rrz/plfs/plfs-2.5-mdhim/share/man/man3/plfs_chmod.3"
    "/usr/projects/plfs/rrz/plfs/plfs-2.5-mdhim/share/man/man3/plfs_mkdir.3"
    "/usr/projects/plfs/rrz/plfs/plfs-2.5-mdhim/share/man/man3/plfs_readlink.3"
    "/usr/projects/plfs/rrz/plfs/plfs-2.5-mdhim/share/man/man3/plfs_setxattr.3"
    "/usr/projects/plfs/rrz/plfs/plfs-2.5-mdhim/share/man/man3/plfs_statvfs.3"
    "/usr/projects/plfs/rrz/plfs/plfs-2.5-mdhim/share/man/man3/plfs_flush_writes.3"
    "/usr/projects/plfs/rrz/plfs/plfs-2.5-mdhim/share/man/man3/plfs_invalidate_read_cache.3"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/man/man5" TYPE FILE FILES "/usr/projects/plfs/rrz/plfs/plfs-2.5-mdhim/share/man/man5/plfsrc.5")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/man/man7" TYPE FILE FILES "/usr/projects/plfs/rrz/plfs/plfs-2.5-mdhim/share/man/man7/plfs.7")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  INCLUDE("/usr/projects/plfs/rrz/plfs/plfs-2.5-mdhim/yaml-cpp/cmake_install.cmake")
  INCLUDE("/usr/projects/plfs/rrz/plfs/plfs-2.5-mdhim/tests/cmake_install.cmake")
  INCLUDE("/usr/projects/plfs/rrz/plfs/plfs-2.5-mdhim/man/cmake_install.cmake")

ENDIF(NOT CMAKE_INSTALL_LOCAL_ONLY)

IF(CMAKE_INSTALL_COMPONENT)
  SET(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
ELSE(CMAKE_INSTALL_COMPONENT)
  SET(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
ENDIF(CMAKE_INSTALL_COMPONENT)

FILE(WRITE "/usr/projects/plfs/rrz/plfs/plfs-2.5-mdhim/${CMAKE_INSTALL_MANIFEST}" "")
FOREACH(file ${CMAKE_INSTALL_MANIFEST_FILES})
  FILE(APPEND "/usr/projects/plfs/rrz/plfs/plfs-2.5-mdhim/${CMAKE_INSTALL_MANIFEST}" "${file}\n")
ENDFOREACH(file)
