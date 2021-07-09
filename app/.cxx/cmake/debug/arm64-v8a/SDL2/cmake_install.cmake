# Install script for directory: C:/Programming/android/GameEngine/app/jni/SDL2

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Programming/android/GameEngine/app/.cxx/cmake/debug/arm64-v8a/SDL2/libSDL2.a")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "C:/Programming/android/GameEngine/app/build/intermediates/cmake/debug/obj/arm64-v8a/libSDL2.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libSDL2.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libSDL2.so")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "C:/Users/xXRag/AppData/Local/Android/Sdk/ndk/21.4.7075529/toolchains/llvm/prebuilt/windows-x86_64/bin/aarch64-linux-android-strip.exe" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libSDL2.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Programming/android/GameEngine/app/.cxx/cmake/debug/arm64-v8a/SDL2/libSDL2main.a")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "C:/Programming/android/GameEngine/app/build/intermediates/cmake/debug/obj/arm64-v8a/libhidapi.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libhidapi.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libhidapi.so")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "C:/Users/xXRag/AppData/Local/Android/Sdk/ndk/21.4.7075529/toolchains/llvm/prebuilt/windows-x86_64/bin/aarch64-linux-android-strip.exe" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libhidapi.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL2/SDL2Targets.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL2/SDL2Targets.cmake"
         "C:/Programming/android/GameEngine/app/.cxx/cmake/debug/arm64-v8a/SDL2/CMakeFiles/Export/lib/cmake/SDL2/SDL2Targets.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL2/SDL2Targets-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL2/SDL2Targets.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL2" TYPE FILE FILES "C:/Programming/android/GameEngine/app/.cxx/cmake/debug/arm64-v8a/SDL2/CMakeFiles/Export/lib/cmake/SDL2/SDL2Targets.cmake")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL2" TYPE FILE FILES "C:/Programming/android/GameEngine/app/.cxx/cmake/debug/arm64-v8a/SDL2/CMakeFiles/Export/lib/cmake/SDL2/SDL2Targets-debug.cmake")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xDevelx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL2" TYPE FILE FILES
    "C:/Programming/android/GameEngine/app/jni/SDL2/SDL2Config.cmake"
    "C:/Programming/android/GameEngine/app/.cxx/cmake/debug/arm64-v8a/SDL2ConfigVersion.cmake"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/SDL2" TYPE FILE FILES
    "C:/Programming/android/GameEngine/app/jni/SDL2/include/SDL.h"
    "C:/Programming/android/GameEngine/app/jni/SDL2/include/SDL_assert.h"
    "C:/Programming/android/GameEngine/app/jni/SDL2/include/SDL_atomic.h"
    "C:/Programming/android/GameEngine/app/jni/SDL2/include/SDL_audio.h"
    "C:/Programming/android/GameEngine/app/jni/SDL2/include/SDL_bits.h"
    "C:/Programming/android/GameEngine/app/jni/SDL2/include/SDL_blendmode.h"
    "C:/Programming/android/GameEngine/app/jni/SDL2/include/SDL_clipboard.h"
    "C:/Programming/android/GameEngine/app/jni/SDL2/include/SDL_config_android.h"
    "C:/Programming/android/GameEngine/app/jni/SDL2/include/SDL_config_iphoneos.h"
    "C:/Programming/android/GameEngine/app/jni/SDL2/include/SDL_config_macosx.h"
    "C:/Programming/android/GameEngine/app/jni/SDL2/include/SDL_config_minimal.h"
    "C:/Programming/android/GameEngine/app/jni/SDL2/include/SDL_config_os2.h"
    "C:/Programming/android/GameEngine/app/jni/SDL2/include/SDL_config_pandora.h"
    "C:/Programming/android/GameEngine/app/jni/SDL2/include/SDL_config_psp.h"
    "C:/Programming/android/GameEngine/app/jni/SDL2/include/SDL_config_windows.h"
    "C:/Programming/android/GameEngine/app/jni/SDL2/include/SDL_config_winrt.h"
    "C:/Programming/android/GameEngine/app/jni/SDL2/include/SDL_config_wiz.h"
    "C:/Programming/android/GameEngine/app/jni/SDL2/include/SDL_copying.h"
    "C:/Programming/android/GameEngine/app/jni/SDL2/include/SDL_cpuinfo.h"
    "C:/Programming/android/GameEngine/app/jni/SDL2/include/SDL_egl.h"
    "C:/Programming/android/GameEngine/app/jni/SDL2/include/SDL_endian.h"
    "C:/Programming/android/GameEngine/app/jni/SDL2/include/SDL_error.h"
    "C:/Programming/android/GameEngine/app/jni/SDL2/include/SDL_events.h"
    "C:/Programming/android/GameEngine/app/jni/SDL2/include/SDL_filesystem.h"
    "C:/Programming/android/GameEngine/app/jni/SDL2/include/SDL_gamecontroller.h"
    "C:/Programming/android/GameEngine/app/jni/SDL2/include/SDL_gesture.h"
    "C:/Programming/android/GameEngine/app/jni/SDL2/include/SDL_haptic.h"
    "C:/Programming/android/GameEngine/app/jni/SDL2/include/SDL_hints.h"
    "C:/Programming/android/GameEngine/app/jni/SDL2/include/SDL_joystick.h"
    "C:/Programming/android/GameEngine/app/jni/SDL2/include/SDL_keyboard.h"
    "C:/Programming/android/GameEngine/app/jni/SDL2/include/SDL_keycode.h"
    "C:/Programming/android/GameEngine/app/jni/SDL2/include/SDL_loadso.h"
    "C:/Programming/android/GameEngine/app/jni/SDL2/include/SDL_locale.h"
    "C:/Programming/android/GameEngine/app/jni/SDL2/include/SDL_log.h"
    "C:/Programming/android/GameEngine/app/jni/SDL2/include/SDL_main.h"
    "C:/Programming/android/GameEngine/app/jni/SDL2/include/SDL_messagebox.h"
    "C:/Programming/android/GameEngine/app/jni/SDL2/include/SDL_metal.h"
    "C:/Programming/android/GameEngine/app/jni/SDL2/include/SDL_misc.h"
    "C:/Programming/android/GameEngine/app/jni/SDL2/include/SDL_mouse.h"
    "C:/Programming/android/GameEngine/app/jni/SDL2/include/SDL_mutex.h"
    "C:/Programming/android/GameEngine/app/jni/SDL2/include/SDL_name.h"
    "C:/Programming/android/GameEngine/app/jni/SDL2/include/SDL_opengl.h"
    "C:/Programming/android/GameEngine/app/jni/SDL2/include/SDL_opengl_glext.h"
    "C:/Programming/android/GameEngine/app/jni/SDL2/include/SDL_opengles.h"
    "C:/Programming/android/GameEngine/app/jni/SDL2/include/SDL_opengles2.h"
    "C:/Programming/android/GameEngine/app/jni/SDL2/include/SDL_opengles2_gl2.h"
    "C:/Programming/android/GameEngine/app/jni/SDL2/include/SDL_opengles2_gl2ext.h"
    "C:/Programming/android/GameEngine/app/jni/SDL2/include/SDL_opengles2_gl2platform.h"
    "C:/Programming/android/GameEngine/app/jni/SDL2/include/SDL_opengles2_khrplatform.h"
    "C:/Programming/android/GameEngine/app/jni/SDL2/include/SDL_pixels.h"
    "C:/Programming/android/GameEngine/app/jni/SDL2/include/SDL_platform.h"
    "C:/Programming/android/GameEngine/app/jni/SDL2/include/SDL_power.h"
    "C:/Programming/android/GameEngine/app/jni/SDL2/include/SDL_quit.h"
    "C:/Programming/android/GameEngine/app/jni/SDL2/include/SDL_rect.h"
    "C:/Programming/android/GameEngine/app/jni/SDL2/include/SDL_render.h"
    "C:/Programming/android/GameEngine/app/jni/SDL2/include/SDL_revision.h"
    "C:/Programming/android/GameEngine/app/jni/SDL2/include/SDL_rwops.h"
    "C:/Programming/android/GameEngine/app/jni/SDL2/include/SDL_scancode.h"
    "C:/Programming/android/GameEngine/app/jni/SDL2/include/SDL_sensor.h"
    "C:/Programming/android/GameEngine/app/jni/SDL2/include/SDL_shape.h"
    "C:/Programming/android/GameEngine/app/jni/SDL2/include/SDL_stdinc.h"
    "C:/Programming/android/GameEngine/app/jni/SDL2/include/SDL_surface.h"
    "C:/Programming/android/GameEngine/app/jni/SDL2/include/SDL_system.h"
    "C:/Programming/android/GameEngine/app/jni/SDL2/include/SDL_syswm.h"
    "C:/Programming/android/GameEngine/app/jni/SDL2/include/SDL_test.h"
    "C:/Programming/android/GameEngine/app/jni/SDL2/include/SDL_test_assert.h"
    "C:/Programming/android/GameEngine/app/jni/SDL2/include/SDL_test_common.h"
    "C:/Programming/android/GameEngine/app/jni/SDL2/include/SDL_test_compare.h"
    "C:/Programming/android/GameEngine/app/jni/SDL2/include/SDL_test_crc32.h"
    "C:/Programming/android/GameEngine/app/jni/SDL2/include/SDL_test_font.h"
    "C:/Programming/android/GameEngine/app/jni/SDL2/include/SDL_test_fuzzer.h"
    "C:/Programming/android/GameEngine/app/jni/SDL2/include/SDL_test_harness.h"
    "C:/Programming/android/GameEngine/app/jni/SDL2/include/SDL_test_images.h"
    "C:/Programming/android/GameEngine/app/jni/SDL2/include/SDL_test_log.h"
    "C:/Programming/android/GameEngine/app/jni/SDL2/include/SDL_test_md5.h"
    "C:/Programming/android/GameEngine/app/jni/SDL2/include/SDL_test_memory.h"
    "C:/Programming/android/GameEngine/app/jni/SDL2/include/SDL_test_random.h"
    "C:/Programming/android/GameEngine/app/jni/SDL2/include/SDL_thread.h"
    "C:/Programming/android/GameEngine/app/jni/SDL2/include/SDL_timer.h"
    "C:/Programming/android/GameEngine/app/jni/SDL2/include/SDL_touch.h"
    "C:/Programming/android/GameEngine/app/jni/SDL2/include/SDL_types.h"
    "C:/Programming/android/GameEngine/app/jni/SDL2/include/SDL_version.h"
    "C:/Programming/android/GameEngine/app/jni/SDL2/include/SDL_video.h"
    "C:/Programming/android/GameEngine/app/jni/SDL2/include/SDL_vulkan.h"
    "C:/Programming/android/GameEngine/app/jni/SDL2/include/begin_code.h"
    "C:/Programming/android/GameEngine/app/jni/SDL2/include/close_code.h"
    "C:/Programming/android/GameEngine/app/.cxx/cmake/debug/arm64-v8a/SDL2/include/SDL_config.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Programming/android/GameEngine/app/.cxx/cmake/debug/arm64-v8a/SDL2/sdl2.pc")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE PROGRAM FILES "C:/Programming/android/GameEngine/app/.cxx/cmake/debug/arm64-v8a/SDL2/sdl2-config")
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
file(INSTALL DESTINATION "C:/Program Files (x86)/GAME/share/aclocal" TYPE FILE FILES "C:/Programming/android/GameEngine/app/jni/SDL2/sdl2.m4")
endif()

