function (enable_compiler_warnings TARGET_NAME)
  target_compile_options(
    ${TARGET_NAME}
    PRIVATE -Wall
            -Wextra # reasonable and standard
            -Werror # treat compiler warnings as errors
            -Wshadow # warn the user if a variable declaration shadows one from a parent context
            -Wnon-virtual-dtor # warn the user if a class with virtual functions has a non-virtual destructor,
            -Wold-style-cast # warn for c-style casts
            -Wcast-align # warn for potential performance problem casts
            -Wunused # warn on anything being unused
            -Woverloaded-virtual # warn if you overload (not override) a virtual function
            -Wpedantic # warn if non-standard C++ is used
            -Wconversion # warn on type conversions that may lose data
            -Wsign-conversion # warn on sign conversions
            -Wnull-dereference # warn if a null dereference is detected
            -Wdouble-promotion # warn if float is implicit promoted to double
            -Wformat=2 # warn on security issues around functions that format output (i.e. printf)
  )
endfunction ()
