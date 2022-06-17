project 'spdlog'
  location '%{wks.location}/Source/ThirdParty/spdlog'
  kind 'StaticLib'
  language 'C++'
  cppdialect 'C++20'
  staticruntime 'on'

  targetdir(build_directory)
  objdir(int_build_directory)

  files
  {
    '%{prj.location}/src/**.cpp',
    '%{prj.location}/include/**.h',
    '%{prj.location}/include/**.rst',
  }

  includedirs
  {
    '%{prj.location}/include',
    '%{prj.location}/src',
  }

  defines
  {
    'SPDLOG_COMPILED_LIB',
  }