FILE(REMOVE_RECURSE
  "../msg_gen"
  "../src/rover_calibrate/msg"
  "../msg_gen"
  "CMakeFiles/ROSBUILD_genmsg_lisp"
  "../msg_gen/lisp/ScanAngle.lisp"
  "../msg_gen/lisp/_package.lisp"
  "../msg_gen/lisp/_package_ScanAngle.lisp"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/ROSBUILD_genmsg_lisp.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
