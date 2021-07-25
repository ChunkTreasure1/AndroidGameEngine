# Install script for directory: D:/Programming/AndroidGameEngine/app/jni/SDL2

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/GAME")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "0")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "TRUE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "D:/Programming/AndroidGameEngine/app/.cxx/cmake/debug/x86/SDL2/libSDL2.a")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "D:/Programming/AndroidGameEngine/app/build/intermediates/cmake/debug/obj/x86/libSDL2.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libSDL2.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libSDL2.so")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "C:/Users/ivar/AppData/Local/Android/Sdk/ndk/21.4.7075529/toolchains/llvm/prebuilt/windows-x86_64/bin/i686-linux-android-strip.exe" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libSDL2.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "D:/Programming/AndroidGameEngine/app/.cxx/cmake/debug/x86/SDL2/libSDL2main.a")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "D:/Programming/AndroidGameEngine/app/build/intermediates/cmake/debug/obj/x86/libhidapi.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libhidapi.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libhidapi.so")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "C:/Users/ivar/AppData/Local/Android/Sdk/ndk/21.4.7075529/toolchains/llvm/prebuilt/windows-x86_64/bin/i686-linux-android-strip.exe" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libhidapi.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL2/SDL2Targets.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL2/SDL2Targets.cmake"
         "D:/Programming/AndroidGameEngine/app/.cxx/cmake/debug/x86/SDL2/CMakeFiles/Export/lib/cmake/SDL2/SDL2Targets.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL2/SDL2Targets-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL2/SDL2Targets.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL2" TYPE FILE FILES "D:/Programming/AndroidGameEngine/app/.cxx/cmake/debug/x86/SDL2/CMakeFiles/Export/lib/cmake/SDL2/SDL2Targets.cmake")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL2" TYPE FILE FILES "D:/Programming/AndroidGameEngine/app/.cxx/cmake/debug/x86/SDL2/CMakeFiles/Export/lib/cmake/SDL2/SDL2Targets-debug.cmake")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xDevelx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL2" TYPE FILE FILES
    "D:/Programming/AndroidGameEngine/app/jni/SDL2/SDL2Config.cmake"
    "D:/Programming/AndroidGameEngine/app/.cxx/cmake/debug/x86/SDL2ConfigVersion.cmake"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/SDL2" TYPE FILE FILES
    "D:/Programming/AndroidGameEngine/app/jni/SDL2/include/SDL.h"
    "D:/Programming/AndroidGameEngine/app/jni/SDL2/include/SDL_assert.h"
    "D:/Programming/AndroidGameEngine/app/jni/SDL2/include/SDL_atomic.h"
    "D:/Programming/AndroidGameEngine/app/jni/SDL2/include/SDL_audio.h"
    "D:/Programming/AndroidGameEngine/app/jni/SDL2/include/SDL_bits.h"
    "D:/Programming/AndroidGameEngine/app/jni/SDL2/include/SDL_blendmode.h"
    "D:/Programming/AndroidGameEngine/app/jni/SDL2/include/SDL_clipboard.h"
    "D:/Programming/AndroidGameEngine/app/jni/SDL2/include/SDL_config_android.h"
    "D:/Programming/AndroidGameEngine/app/jni/SDL2/include/SDL_config_iphoneos.h"
    "D:/Programming/AndroidGameEngine/app/jni/SDL2/include/SDL_config_macosx.h"
    "D:/Programming/AndroidGameEngine/app/jni/SDL2/include/SDL_config_minimal.h"
    "D:/Programming/AndroidGameEngine/app/jni/SDL2/include/SDL_config_os2.h"
    "D:/Programming/AndroidGameEngine/app/jni/SDL2/include/SDL_config_pandora.h"
    "D:/Programming/AndroidGameEngine/app/jni/SDL2/include/SDL_config_psp.h"
    "D:/Programming/AndroidGameEngine/app/jni/SDL2/include/SDL_config_windows.h"
    "D:/Programming/AndroidGameEngine/app/jni/SDL2/include/SDL_config_winrt.h"
    "D:/Programming/AndroidGameEngine/app/jni/SDL2/include/SDL_config_wiz.h"
    "D:/Programming/AndroidGameEngine/app/jni/SDL2/include/SDL_copying.h"
    "D:/Programming/AndroidGameEngine/app/jni/SDL2/include/SDL_cpuinfo.h"
    "D:/Programming/AndroidGameEngine/app/jni/SDL2/include/SDL_egl.h"
    "D:/Programming/AndroidGameEngine/app/jni/SDL2/include/SDL_endian.h"
    "D:/Programming/AndroidGameEngine/app/jni/SDL2/include/SDL_error.h"
    "D:/Programming/AndroidGameEngine/app/jni/SDL2/include/SDL_events.h"
    "D:/Programming/AndroidGameEngine/app/jni/SDL2/include/SDL_filesystem.h"
    "D:/Programming/AndroidGameEngine/app/jni/SDL2/include/SDL_gamecontroller.h"
    "D:/Programming/AndroidGameEngine/app/jni/SDL2/include/SDL_gesture.h"
    "D:/Programming/AndroidGameEngine/app/jni/SDL2/include/SDL_haptic.h"
    "D:/Programming/AndroidGameEngine/app/jni/SDL2/include/SDL_hints.h"
    "D:/Programming/AndroidGameEngine/app/jni/SDL2/include/SDL_joystick.h"
    "D:/Programming/AndroidGameEngine/app/jni/SDL2/include/SDL_keyboard.h"
    "D:/Programming/AndroidGameEngine/app/jni/SDL2/include/SDL_keycode.h"
    "D:/Programming/AndroidGameEngine/app/jni/SDL2/include/SDL_loadso.h"
    "D:/Programming/AndroidGameEngine/app/jni/SDL2/include/SDL_locale.h"
    "D:/Programming/AndroidGameEngine/app/jni/SDL2/include/SDL_log.h"
    "D:/Programming/AndroidGameEngine/app/jni/SDL2/include/SDL_main.h"
    "D:/Programming/AndroidGameEngine/app/jni/SDL2/include/SDL_messagebox.h"
    "D:/Programming/AndroidGameEngine/app/jni/SDL2/include/SDL_metal.h"
    "D:/Programming/AndroidGameEngine/app/jni/SDL2/include/SDL_misc.h"
    "D:/Programming/AndroidGameEngine/app/jni/SDL2/include/SDL_mouse.h"
    "D:/Programming/AndroidGameEngine/app/jni/SDL2/include/SDL_mutex.h"
    "D:/Programming/AndroidGameEngine/app/jni/SDL2/include/SDL_name.h"
    "D:/Programming/AndroidGameEngine/app/jni/SDL2/include/SDL_opengl.h"
    "D:/Programming/AndroidGameEngine/app/jni/SDL2/include/SDL_opengl_glext.h"
    "D:/Programming/AndroidGameEngine/app/jni/SDL2/include/SDL_opengles.h"
    "D:/Programming/AndroidGameEngine/app/jni/SDL2/include/SDL_opengles2.h"
    "D:/Programming/AndroidGameEngine/app/jni/SDL2/include/SDL_opengles2_gl2.h"
    "D:/Programming/AndroidGameEngine/app/jni/SDL2/include/SDL_opengles2_gl2ext.h"
    "D:/Programming/AndroidGameEngine/app/jni/SDL2/include/SDL_opengles2_gl2platform.h"
    "D:/Programming/AndroidGameEngine/app/jni/SDL2/include/SDL_opengles2_khrplatform.h"
    "D:/Programming/AndroidGameEngine/app/jni/SDL2/include/SDL_pixels.h"
    "D:/Programming/AndroidGameEngine/app/jni/SDL2/include/SDL_platform.h"
    "D:/Programming/AndroidGameEngine/app/jni/SDL2/include/SDL_power.h"
    "D:/Programming/AndroidGameEngine/app/jni/SDL2/include/SDL_quit.h"
    "D:/Programming/AndroidGameEngine/app/jni/SDL2/include/SDL_rect.h"
    "D:/Programming/AndroidGameEngine/app/jni/SDL2/include/SDL_render.h"
    "D:/Programming/AndroidGameEngine/app/jni/SDL2/include/SDL_revision.h"
    "D:/Programming/AndroidGameEngine/app/jni/SDL2/include/SDL_rwops.h"
    "D:/Programming/AndroidGameEngine/app/jni/SDL2/include/SDL_scancode.h"
    "D:/Programming/AndroidGameEngine/app/jni/SDL2/include/SDL_sensor.h"
    "D:/Programming/AndroidGameEngine/app/jni/SDL2/include/SDL_shape.h"
    "D:/Programming/AndroidGameEngine/app/jni/SDL2/include/SDL_stdinc.h"
    "D:/Programming/AndroidGameEngine/app/jni/SDL2/include/SDL_surface.h"
    "D:/Programming/AndroidGameEngine/app/jni/SDL2/include/SDL_system.h"
    "D:/Programming/AndroidGameEngine/app/jni/SDL2/include/SDL_syswm.h"
    "D:/Programming/AndroidGameEngine/app/jni/SDL2/include/SDL_test.h"
    "D:/Programming/AndroidGameEngine/app/jni/SDL2/include/SDL_test_assert.h"
    "D:/Programming/AndroidGameEngine/app/jni/SDL2/include/SDL_test_common.h"
    "D:/Programming/AndroidGameEngine/app/jni/SDL2/include/SDL_test_compare.h"
    "D:/Programming/AndroidGameEngine/app/jni/SDL2/include/SDL_test_crc32.h"
    "D:/Programming/AndroidGameEngine/app/jni/SDL2/include/SDL_test_font.h"
    "D:/Programming/AndroidGameEngine/app/jni/SDL2/include/SDL_test_fuzzer.h"
    "D:/Programming/AndroidGameEngine/app/jni/SDL2/include/SDL_test_harness.h"
    "D:/Programming/AndroidGameEngine/app/jni/SDL2/include/SDL_test_images.h"
    "D:/Programming/AndroidGameEngine/app/jni/SDL2/include/SDL_test_log.h"
    "D:/Programming/AndroidGameEngine/app/jni/SDL2/include/SDL_test_md5.h"
    "D:/Programming/AndroidGameEngine/app/jni/SDL2/include/SDL_test_memory.h"
    "D:/Programming/AndroidGameEngine/app/jni/SDL2/include/SDL_test_random.h"
    "D:/Programming/AndroidGameEngine/app/jni/SDL2/include/SDL_thread.h"
    "D:/Programming/AndroidGameEngine/app/jni/SDL2/include/SDL_timer.h"
    "D:/Programming/AndroidGameEngine/app/jni/SDL2/include/SDL_touch.h"
    "D:/Programming/AndroidGameEngine/app/jni/SDL2/include/SDL_types.h"
    "D:/Programming/AndroidGameEngine/app/jni/SDL2/include/SDL_version.h"
    "D:/Programming/AndroidGameEngine/app/jni/SDL2/include/SDL_video.h"
    "D:/Programming/AndroidGameEngine/app/jni/SDL2/include/SDL_vulkan.h"
    "D:/Programming/AndroidGameEngine/app/jni/SDL2/include/begin_code.h"
    "D:/Programming/AndroidGameEngine/app/jni/SDL2/include/close_code.h"
    "D:/Programming/AndroidGameEngine/app/.cxx/cmake/debug/x86/SDL2/include/SDL_config.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "D:/Programming/AndroidGameEngine/app/.cxx/cmake/debug/x86/SDL2/sdl2.pc")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE PROGRAM FILES "D:/Programming/AndroidGameEngine/app/.cxx/cmake/debug/x86/SDL2/sdl2-config")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "C:/Program Files (x86)/GAME/share/aclocal/sdl2.m4")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "C:/Program Files (x86)/GAME/share/aclocal" TYPE FILE FILES "D:/Programming/AndroidGameEngine/app/jni/SDL2/sdl2.m4")
endif()

