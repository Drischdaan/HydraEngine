project 'Sandbox'
  location '%{wks.location}/Source/Examples/%{prj.name}'
  kind 'ConsoleApp'
  language 'C++'
  cppdialect 'C++20'
  staticruntime 'on'

  targetdir(build_directory)
  objdir(int_build_directory)

  files {
    '%{prj.location}/src/**.h',
    '%{prj.location}/src/**.cpp',
    '%{prj.location}/src/**.hpp',
  }

  includedirs {
    '%{prj.location}/src',
    '%{prj.location}/src/Private',
    '%{prj.location}/src/Public',
    '%{wks.location}/Source/Engine/src/Public',
  }

  libdirs {

  }

  links {
    'Hydra',
  }

  defines {
    '_CRT_SECURE_NO_WARNINGS'
  }

  -- Kind Filters
  filter 'kind:SharedLib'
    linkoptions { '-IGNORE:4251' }
    disablewarnings { '4251' }
  
    defines {
      '_LINKING_SHARED'
    }
  
  filter 'kind:StaticLib'
    defines {
      '_LINKING_STATIC'
    }
  
  
  
  -- Systen Filters
  filter 'system:windows'
    systemversion 'latest'
  
    filter 'kind:SharedLib'
      defines {
        '_BUILD_LIBRARY',
      }
  
  
  
  -- Configuration Filters
  filter 'configurations:Debug'
    runtime 'Debug'
    symbols 'On'
  
    defines {
      '_CONFIGURATION_DEBUG'
    }
  
  filter 'configurations:Release'
    runtime 'Release'
    optimize 'On'
  
    defines {
      '_CONFIGURATION_RELEASE'
    }
  
  filter 'configurations:Distribution'
    runtime 'Release'
    optimize 'On'
  
    defines {
      '_CONFIGURATION_DISTRIBUTION'
    }