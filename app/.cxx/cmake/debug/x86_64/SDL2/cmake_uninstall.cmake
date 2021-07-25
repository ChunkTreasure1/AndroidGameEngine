if (NOT EXISTS "/home/chunktreasure/StudioProjects/AndroidGameEngine/app/.cxx/cmake/debug/x86_64/install_manifest.txt")
    message(FATAL_ERROR "Cannot find install manifest: \"/home/chunktreasure/StudioProjects/AndroidGameEngine/app/.cxx/cmake/debug/x86_64/install_manifest.txt\"")
endif(NOT EXISTS "/home/chunktreasure/StudioProjects/AndroidGameEngine/app/.cxx/cmake/debug/x86_64/install_manifest.txt")

file(READ "/home/chunktreasure/StudioProjects/AndroidGameEngine/app/.cxx/cmake/debug/x86_64/install_manifest.txt" files)
string(REGEX REPLACE "\n" ";" files "${files}")
foreach (file ${files})
    message(STATUS "Uninstalling \"$ENV{DESTDIR}${file}\"")
    execute_process(
        COMMAND /home/chunktreasure/Android/Sdk/cmake/3.10.2.4988404/bin/cmake -E remove "$ENV{DESTDIR}${file}"
        OUTPUT_VARIABLE rm_out
        RESULT_VARIABLE rm_retval
    )
    if(NOT ${rm_retval} EQUAL 0)
        message(FATAL_ERROR "Problem when removing \"$ENV{DESTDIR}${file}\"")
    endif (NOT ${rm_retval} EQUAL 0)
endforeach(file)

